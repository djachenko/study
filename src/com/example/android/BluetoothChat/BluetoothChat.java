package com.example.android.BluetoothChat;

import android.app.Activity;
import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.provider.MediaStore;
import android.speech.RecognizerIntent;
import android.util.Log;
import android.view.*;
import android.view.inputmethod.EditorInfo;
import android.widget.*;

import java.util.ArrayList;

public class BluetoothChat extends Activity
{
    private static final String TAG = "BluetoothChat";

    public static final int MESSAGE_STATE_CHANGE = 1;
    public static final int MESSAGE_READ = 2;
    public static final int MESSAGE_WRITE = 3;
    public static final int MESSAGE_DEVICE_NAME = 4;
    public static final int MESSAGE_TOAST = 5;
    public static final int MESSAGE_AVATAR = 6;

    // Key names received from the BluetoothChatService Handler
    public static final String DEVICE_NAME = "device_name";
    public static final String TOAST = "toast";

    private static final int REQUEST_CONNECT_DEVICE_SECURE = 1;
    private static final int REQUEST_CONNECT_DEVICE_INSECURE = 2;
    private static final int REQUEST_ENABLE_BT = 3;
    private static final int VOICE_RECOGNITION_REQUEST_CODE = 8;
    private static final int REQUEST_AVATAR_PHOTO = 4;

    private ListView mConversationView;
    private EditText mOutEditText;

    private Bitmap avatar;

    private String mConnectedDeviceName = null;
    private ArrayAdapter<String> mConversationArrayAdapter;
    private StringBuffer mOutStringBuffer;
    private BluetoothAdapter mBluetoothAdapter = null;
    private BluetoothChatService mChatService = null;

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.main);

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

        if (!mBluetoothAdapter.isEnabled())
        {
            Intent enableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableIntent, REQUEST_ENABLE_BT);
        }
        else
        {
            if (mChatService == null) setupChat();
        }
    }

    @Override
    public synchronized void onResume()
    {
        super.onResume();

        // Performing this check in onResume() covers the case in which BT was
        // not enabled during onStart(), so we were paused to enable it...
        // onResume() will be called when ACTION_REQUEST_ENABLE activity returns.
        if (mChatService != null)
        {
            // Only if the state is STATE_NONE, do we know that we haven't started already
            if (mChatService.getState() == BluetoothChatService.STATE_NONE)
            {
                mChatService.start();
            }
        }
    }

    private void setupChat()
    {
        Log.d(TAG, "setupChat()");

        mConversationArrayAdapter = new ArrayAdapter<String>(this, R.layout.message);
        mConversationView = (ListView) findViewById(R.id.in);
        mConversationView.setAdapter(mConversationArrayAdapter);

        mOutEditText = (EditText) findViewById(R.id.edit_text_out);
        mOutEditText.setOnEditorActionListener(mWriteListener);

        mChatService = new BluetoothChatService(mHandler);

        mOutStringBuffer = new StringBuffer("");

        AlertDialog.Builder builder = new AlertDialog.Builder(BluetoothChat.this);
        builder.setTitle("Hello!!")
                .setMessage("Now you have to take picture on your avatar ;)")
                .setCancelable(false)
                .setNegativeButton("OK",
                        new DialogInterface.OnClickListener()
                        {
                            public void onClick(DialogInterface dialog, int id)
                            {
                                Intent takePictureIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
                                startActivityForResult(takePictureIntent, REQUEST_AVATAR_PHOTO);
                                dialog.cancel();
                            }
                        });
        AlertDialog alert = builder.create();
        alert.show();
    }

    public void startVoiceRecognitionActivity(View view)
    {
        Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL, RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
        intent.putExtra(RecognizerIntent.EXTRA_PROMPT, "Speech recognition demo");
        startActivityForResult(intent, VOICE_RECOGNITION_REQUEST_CODE);
    }

    public void sendButtonHandler(View view)
    {
        String message = mOutEditText.getText().toString();
        sendMessage(message);
    }

    @Override
    public void onDestroy()
    {
        super.onDestroy();

        if (mChatService != null)
        {
            mChatService.stop();
        }
    }

    private void ensureDiscoverable()
    {
        if (mBluetoothAdapter.getScanMode() != BluetoothAdapter.SCAN_MODE_CONNECTABLE_DISCOVERABLE)
        {
            Intent discoverableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);
            discoverableIntent.putExtra(BluetoothAdapter.EXTRA_DISCOVERABLE_DURATION, 300);
            startActivity(discoverableIntent);
        }
    }

    private void sendMessage(String message)
    {
        if (mChatService.getState() != BluetoothChatService.STATE_CONNECTED)
        {
            Toast.makeText(this, R.string.not_connected, Toast.LENGTH_SHORT).show();
            return;
        }

        if (message.length() > 0)
        {
            byte[] send = message.getBytes();
            mChatService.write(send);

            mOutStringBuffer.setLength(0);
            mOutEditText.setText(mOutStringBuffer);
        }
    }

    private TextView.OnEditorActionListener mWriteListener =
            new TextView.OnEditorActionListener()
            {
                public boolean onEditorAction(TextView view, int actionId, KeyEvent event)
                {
                    if (actionId == EditorInfo.IME_NULL && event.getAction() == KeyEvent.ACTION_UP)
                    {
                        String message = view.getText().toString();
                        sendMessage(message);
                    }

                    return true;
                }
            };


    private final Handler mHandler = new Handler()
    {
        @Override
        public void handleMessage(Message msg)
        {
            switch (msg.what)
            {
                case MESSAGE_STATE_CHANGE:
                    switch (msg.arg1)
                    {
                        case BluetoothChatService.STATE_CONNECTED:
                            mConversationArrayAdapter.clear();
                            break;
                        case BluetoothChatService.STATE_LISTEN:
                        case BluetoothChatService.STATE_NONE:
                            TextView nickname = (TextView)findViewById(R.id.comp_nickname);
                            nickname.setText(R.string.default_nickname);
                            ImageView view = (ImageView)findViewById(R.id.comp_avatar);
                            view.setImageResource(R.drawable.man);
                            break;
                    }
                    break;
                case MESSAGE_WRITE:
                    byte[] writeBuf = (byte[]) msg.obj;

                    String writeMessage = new String(writeBuf);
                    mConversationArrayAdapter.add("Me:  " + writeMessage);
                    break;
                case MESSAGE_READ:
                    byte[] readBuf = (byte[]) msg.obj;

                    String readMessage = new String(readBuf, 0, msg.arg1);
                    mConversationArrayAdapter.add(mConnectedDeviceName + ":  " + readMessage);
                    break;
                case MESSAGE_DEVICE_NAME:
                    mConnectedDeviceName = msg.getData().getString(DEVICE_NAME);

                    TextView nickname = (TextView)findViewById(R.id.comp_nickname);
                    nickname.setText(mConnectedDeviceName);

                    mChatService.sendAvatar(avatar);

                    Toast.makeText(getApplicationContext(), "Connected to " + mConnectedDeviceName, Toast.LENGTH_SHORT).show();
                    break;
                case MESSAGE_TOAST:
                    Toast.makeText(getApplicationContext(), msg.getData().getString(TOAST),	Toast.LENGTH_LONG).show();
                    break;
                case MESSAGE_AVATAR:
                    byte[] bytes = (byte[])msg.obj;
                    Bitmap otherAvatar = BitmapFactory.decodeByteArray(bytes, 0, bytes.length);

                    ImageView otherAvatarImage = (ImageView)findViewById(R.id.comp_avatar);
                    otherAvatarImage.setImageBitmap(otherAvatar);

                    break;
            }
        }
    };

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        switch (requestCode)
        {
            case REQUEST_CONNECT_DEVICE_SECURE:
                if (resultCode == Activity.RESULT_OK)
                {
                    connectDevice(data, true);
                }
                break;
            case REQUEST_CONNECT_DEVICE_INSECURE:
                if (resultCode == Activity.RESULT_OK)
                {
                    connectDevice(data, false);
                }
                break;
            case REQUEST_ENABLE_BT:
                if (resultCode == Activity.RESULT_OK)
                {
                    setupChat();
                }
                else
                {
                    Log.d(TAG, "BT not enabled");
                    Toast.makeText(this, R.string.bt_not_enabled_leaving, Toast.LENGTH_SHORT).show();
                    finish();
                }
                break;
            case VOICE_RECOGNITION_REQUEST_CODE:
                if (resultCode == Activity.RESULT_OK)
                {
                    ArrayList matches = data.getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);
                    mOutEditText.setText(matches.get(0).toString());
                }

                break;
            case REQUEST_AVATAR_PHOTO:
                if (resultCode == Activity.RESULT_OK)
                {
                    avatar = (Bitmap)data.getExtras().get("data");
                    ImageView imageView = (ImageView)findViewById(R.id.my_avatar);
                    imageView.setImageBitmap(avatar);
                }
        }

        super.onActivityResult(requestCode, resultCode, data);
    }

    private void connectDevice(Intent data, boolean secure)
    {
        String address = data.getExtras().getString(DeviceListActivity.EXTRA_DEVICE_ADDRESS);

        BluetoothDevice device = mBluetoothAdapter.getRemoteDevice(address);

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
                serverIntent = new Intent(this, DeviceListActivity.class);
                startActivityForResult(serverIntent, REQUEST_CONNECT_DEVICE_SECURE);
                return true;
            case R.id.insecure_connect_scan:
                serverIntent = new Intent(this, DeviceListActivity.class);
                startActivityForResult(serverIntent, REQUEST_CONNECT_DEVICE_INSECURE);
                return true;
            case R.id.discoverable:
                ensureDiscoverable();
                return true;
        }
        return false;
    }

}
