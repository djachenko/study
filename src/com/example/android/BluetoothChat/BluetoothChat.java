

package com.example.android.BluetoothChat;

//import android.app.ActionBar;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.provider.MediaStore;
import android.speech.RecognizerIntent;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.inputmethod.EditorInfo;
import android.widget.*;

import java.io.ByteArrayOutputStream;
import java.util.ArrayList;

public class BluetoothChat extends Activity
{
	// Debugging
	private static final String TAG = "BluetoothChat";
	private static final boolean D = true;

	// Message types sent from the BluetoothChatService Handler
	public static final int MESSAGE_STATE_CHANGE = 1;
	public static final int MESSAGE_READ = 2;
	public static final int MESSAGE_WRITE = 3;
	public static final int MESSAGE_DEVICE_NAME = 4;
	public static final int MESSAGE_TOAST = 5;
	public static final int MESSAGE_AVATAR = 6;

	// Key names received from the BluetoothChatService Handler
	public static final String DEVICE_NAME = "device_name";
	public static final String TOAST = "toast";

	// Intent request codes
	private static final int REQUEST_CONNECT_DEVICE_SECURE = 1;
	private static final int REQUEST_CONNECT_DEVICE_INSECURE = 2;
	private static final int REQUEST_ENABLE_BT = 3;
	private static final int VOICE_RECOGNITION_REQUEST_CODE = 8;
	private static final int REQUEST_AVATAR_PHOTO = 4;

	// Layout Views
	private ListView mConversationView;
	private EditText mOutEditText;
	private Button mSendButton;
	private ImageButton mMicButton;
	private TextView view;

	private Bitmap avatar;

	// Name of the connected device
	private String mConnectedDeviceName = null;
	// Array adapter for the conversation thread
	private ArrayAdapter<String> mConversationArrayAdapter;
	// String buffer for outgoing messages
	private StringBuffer mOutStringBuffer;
	// Local Bluetooth adapter
	private BluetoothAdapter mBluetoothAdapter = null;
	// Member object for the chat services
	private BluetoothChatService mChatService = null;


	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		if (D) Log.e(TAG, "+++ ON CREATE +++");

		// Set up the window layout
		setContentView(R.layout.main);

		// Get local Bluetooth adapter
		mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

		// If the adapter is null, then Bluetooth is not supported
		if (mBluetoothAdapter == null)
		{
			Toast.makeText( this, "Bluetooth is not available", Toast.LENGTH_LONG).show();
			finish();
		}
	}

	@Override
	public void onStart()
	{
		super.onStart();
		if (D) Log.e(TAG, "++ ON START ++");

		// If BT is not on, request that it be enabled.
		// setupChat() will then be called during onActivityResult
		if (!mBluetoothAdapter.isEnabled())
		{
			Intent enableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
			startActivityForResult(enableIntent, REQUEST_ENABLE_BT);
			// Otherwise, setup the chat session
		} else
		{
			if (mChatService == null) setupChat();
		}
	}

	@Override
	public synchronized void onResume()
	{
		super.onResume();
		if (D) Log.e(TAG, "+ ON RESUME +");

		// Performing this check in onResume() covers the case in which BT was
		// not enabled during onStart(), so we were paused to enable it...
		// onResume() will be called when ACTION_REQUEST_ENABLE activity returns.
		if (mChatService != null)
		{
			// Only if the state is STATE_NONE, do we know that we haven't started already
			if (mChatService.getState() == BluetoothChatService.STATE_NONE)
			{
				// Start the Bluetooth chat services
				mChatService.start();
			}
		}
	}

	private void setupChat()
	{
		Log.d(TAG, "setupChat()");

		// Initialize the array adapter for the conversation thread
		mConversationArrayAdapter = new ArrayAdapter<String>(this, R.layout.message);
		mConversationView = (ListView) findViewById(R.id.in);
		mConversationView.setAdapter(mConversationArrayAdapter);

		// Initialize the compose field with a listener for the return key
		mOutEditText = (EditText) findViewById(R.id.edit_text_out);
		mOutEditText.setOnEditorActionListener(mWriteListener);

		view = mOutEditText;

		// Initialize the send button with a listener that for click events
		mSendButton = (Button) findViewById(R.id.button_send);
		mSendButton.setOnClickListener(new OnClickListener()
		{
			public void onClick(View v)
			{
				// Send a message using content of the edit text widget
				String message = view.getText().toString();
				sendMessage(message);
			}
		});

		mMicButton = (ImageButton) findViewById(R.id.button_recoder);
		mMicButton.setOnClickListener(new OnClickListener()
		{
			@Override
			public void onClick(View view)
			{
				startVoiceRecognitionActivity();
			}
		});

		// Initialize the BluetoothChatService to perform bluetooth connections
		mChatService = new BluetoothChatService(this, mHandler);

		// Initialize the buffer for outgoing messages
		mOutStringBuffer = new StringBuffer("");

		Intent takePictureIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
		startActivityForResult(takePictureIntent, REQUEST_AVATAR_PHOTO);
	}


	private void startVoiceRecognitionActivity()
	{
		Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
		intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL, RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
		intent.putExtra(RecognizerIntent.EXTRA_PROMPT, "Speech recognition demo");
		startActivityForResult(intent, VOICE_RECOGNITION_REQUEST_CODE);
	}

	@Override
	public synchronized void onPause()
	{
		super.onPause();
		if (D) Log.e(TAG, "- ON PAUSE -");
	}

	@Override
	public void onStop()
	{
		super.onStop();
		if (D) Log.e(TAG, "-- ON STOP --");
	}

	@Override
	public void onDestroy()
	{
		super.onDestroy();
		// Stop the Bluetooth chat services
		if (mChatService != null) mChatService.stop();
		if (D) Log.e(TAG, "--- ON DESTROY ---");
	}

	private void ensureDiscoverable()
	{
		if (D) Log.d(TAG, "ensure discoverable");
		if (mBluetoothAdapter.getScanMode() !=
				BluetoothAdapter.SCAN_MODE_CONNECTABLE_DISCOVERABLE)
		{
			Intent discoverableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);
			discoverableIntent.putExtra(BluetoothAdapter.EXTRA_DISCOVERABLE_DURATION, 300);
			startActivity(discoverableIntent);
		}
	}

	/**
	 * Sends a message.
	 *
	 * @param message A string of text to send.
	 */
	private void sendMessage(String message)
	{
		// Check that we're actually connected before trying anything
		if (mChatService.getState() != BluetoothChatService.STATE_CONNECTED)
		{
			Toast.makeText(this, R.string.not_connected, Toast.LENGTH_SHORT).show();
			return;
		}

		// Check that there's actually something to send
		if (message.length() > 0)
		{
			// Get the message bytes and tell the BluetoothChatService to sendAvatar
			byte[] send = message.getBytes();
			mChatService.write(send);

			// Reset out string buffer to zero and clear the edit text field
			mOutStringBuffer.setLength(0);
			mOutEditText.setText(mOutStringBuffer);
		}
	}

	// The action listener for the EditText widget, to listen for the return key
	private TextView.OnEditorActionListener mWriteListener =
			new TextView.OnEditorActionListener()
			{
				public boolean onEditorAction(TextView view, int actionId, KeyEvent event)
				{
					// If the action is a key-up event on the return key, send the message
					if (actionId == EditorInfo.IME_NULL && event.getAction() == KeyEvent.ACTION_UP)
					{
						String message = view.getText().toString();
						sendMessage(message);
					}
					if (D) Log.i(TAG, "END onEditorAction");
					return true;
				}
			};

   /* private final void setStatus(int resId) {
        final ActionBar actionBar = getActionBar();
        actionBar.setSubtitle(resId);
    }

    private final void setStatus(CharSequence subTitle) {
        final ActionBar actionBar = getActionBar();
        actionBar.setSubtitle(subTitle);
    }*/

	// The Handler that gets information back from the BluetoothChatService
	private final Handler mHandler = new Handler()
	{
		@Override
		public void handleMessage(Message msg)
		{
			switch (msg.what)
			{
				case MESSAGE_STATE_CHANGE:
					if (D) Log.i(TAG, "MESSAGE_STATE_CHANGE: " + msg.arg1);
					switch (msg.arg1)
					{
						case BluetoothChatService.STATE_CONNECTED:
							//  setStatus(getString(R.string.title_connected_to, mConnectedDeviceName));
							mConversationArrayAdapter.clear();
							break;
						case BluetoothChatService.STATE_CONNECTING:
							// setStatus(R.string.title_connecting);
							break;
						case BluetoothChatService.STATE_LISTEN:
						case BluetoothChatService.STATE_NONE:
							// setStatus(R.string.title_not_connected);
							break;
					}
					break;
				case MESSAGE_WRITE:
					byte[] writeBuf = (byte[]) msg.obj;
					// construct a string from the buffer
					String writeMessage = new String(writeBuf);
					mConversationArrayAdapter.add("Me:  " + writeMessage);
					break;
				case MESSAGE_READ:
					byte[] readBuf = (byte[]) msg.obj;
					// construct a string from the valid bytes in the buffer
					String readMessage = new String(readBuf, 0, msg.arg1);
					mConversationArrayAdapter.add(mConnectedDeviceName + ":  " + readMessage);
					break;
				case MESSAGE_DEVICE_NAME:
					// save the connected device's name
					mConnectedDeviceName = msg.getData().getString(DEVICE_NAME);

					TextView nickname = (TextView)findViewById(R.id.nickname);
					nickname.setText(mConnectedDeviceName);

					mChatService.sendAvatar(avatar);

					Toast.makeText(getApplicationContext(), "Connected to " + mConnectedDeviceName, Toast.LENGTH_SHORT).show();
					break;
				case MESSAGE_TOAST:
					Toast.makeText(getApplicationContext(), msg.getData().getString(TOAST),	Toast.LENGTH_SHORT).show();
					break;
				case MESSAGE_AVATAR:
					byte[] bytes = (byte[])msg.obj;
					Bitmap otherAvatar = BitmapFactory.decodeByteArray(bytes, 0, bytes.length);

					ImageView otherAvatarImage = (ImageView)findViewById(R.id.avatar);
					otherAvatarImage.setImageBitmap(otherAvatar);

					break;
			}
		}
	};

	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data)
	{
		if (D) Log.d(TAG, "onActivityResult " + resultCode);
		switch (requestCode)
		{
			case REQUEST_CONNECT_DEVICE_SECURE:
				// When DeviceListActivity returns with a device to connect
				if (resultCode == Activity.RESULT_OK)
				{
					connectDevice(data, true);
				}
				break;
			case REQUEST_CONNECT_DEVICE_INSECURE:
				// When DeviceListActivity returns with a device to connect
				if (resultCode == Activity.RESULT_OK)
				{
					connectDevice(data, false);
				}
				break;
			case REQUEST_ENABLE_BT:
				// When the request to enable Bluetooth returns
				if (resultCode == Activity.RESULT_OK)
				{
					// Bluetooth is now enabled, so set up a chat session
					setupChat();
				}
				else
				{
					// User did not enable Bluetooth or an error occurred
					Log.d(TAG, "BT not enabled");
					Toast.makeText(this, R.string.bt_not_enabled_leaving, Toast.LENGTH_SHORT).show();
					finish();
				}
				break;
			case VOICE_RECOGNITION_REQUEST_CODE:
				if (resultCode == Activity.RESULT_OK)
				{
					// Fill the list view with the strings the recognizer thought it could have heard
					ArrayList matches = data.getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);
					view.setText(matches.get(0).toString());
				}

				break;
			case REQUEST_AVATAR_PHOTO:
				if (resultCode == Activity.RESULT_OK)
				{
					avatar = (Bitmap)data.getExtras().get("data");
					ImageView imageView = (ImageView)findViewById(R.id.avatar);
					imageView.setImageBitmap(avatar);
				}
		}

		super.onActivityResult(requestCode, resultCode, data);
	}

	private void connectDevice(Intent data, boolean secure)
	{
		// Get the device MAC address
		String address = data.getExtras().getString(DeviceListActivity.EXTRA_DEVICE_ADDRESS);
		// Get the BluetoothDevice object
		BluetoothDevice device = mBluetoothAdapter.getRemoteDevice(address);
		// Attempt to connect to the device
		mChatService.connect(device, secure);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu)
	{
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.option_menu, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item)
	{
		Intent serverIntent;
		switch (item.getItemId())
		{
			case R.id.secure_connect_scan:
				// Launch the DeviceListActivity to see devices and do scan
				serverIntent = new Intent(this, DeviceListActivity.class);
				startActivityForResult(serverIntent, REQUEST_CONNECT_DEVICE_SECURE);
				return true;
			case R.id.insecure_connect_scan:
				// Launch the DeviceListActivity to see devices and do scan
				serverIntent = new Intent(this, DeviceListActivity.class);
				startActivityForResult(serverIntent, REQUEST_CONNECT_DEVICE_INSECURE);
				return true;
			case R.id.discoverable:
				// Ensure this device is discoverable by others
				ensureDiscoverable();
				return true;
		}
		return false;
	}

}
