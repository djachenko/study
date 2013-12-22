package com.example.android.BluetoothChat;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothServerSocket;
import android.bluetooth.BluetoothSocket;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;


public class BluetoothChatService
{
    private static final String TAG = "BluetoothChatService";

    private static final String NAME_SECURE = "BluetoothChatSecure";
    private static final String NAME_INSECURE = "BluetoothChatInsecure";

    private static final UUID MY_UUID_SECURE = UUID.fromString("fa87c0d0-afac-11de-8a39-0800200c9a66");
    private static final UUID MY_UUID_INSECURE = UUID.fromString("8ce255c0-200a-11e0-ac64-0800200c9a66");

    private final BluetoothAdapter mAdapter;
    private final Handler mHandler;
    private AcceptThread mSecureAcceptThread;
    private AcceptThread mInsecureAcceptThread;
    private ConnectThread mConnectThread;
    private ConnectedThread mConnectedThread;
    private int mState;

    public static final int STATE_NONE = 0;       // we're doing nothing
    public static final int STATE_LISTEN = 1;     // now listening for incoming connections
    public static final int STATE_CONNECTING = 2; // now initiating an outgoing connection
    public static final int STATE_CONNECTED = 3;  // now connected to a remote device


    public BluetoothChatService(Handler handler)
    {
	    mAdapter = BluetoothAdapter.getDefaultAdapter();
        mState = STATE_NONE;
        mHandler = handler;
    }

    private synchronized void setState(int state)
    {
        mState = state;

        // Give the new state to the Handler so the UI Activity can update
        mHandler.obtainMessage(BluetoothChat.MESSAGE_STATE_CHANGE, state, -1).sendToTarget();
    }

    public synchronized int getState()
    {
        return mState;
    }

    public synchronized void start()
    {
        if (mConnectThread != null)
        {
	        mConnectThread.cancel();
	        mConnectThread = null;
        }

        if (mConnectedThread != null)
        {
	        mConnectedThread.cancel();
	        mConnectedThread = null;
        }

        setState(STATE_LISTEN);

        if (mSecureAcceptThread == null)
        {
            mSecureAcceptThread = new AcceptThread(true);
            mSecureAcceptThread.start();
        }

        if (mInsecureAcceptThread == null)
        {
            mInsecureAcceptThread = new AcceptThread(false);
            mInsecureAcceptThread.start();
        }
    }

    public synchronized void connect(BluetoothDevice device, boolean secure)
    {
        if (mState == STATE_CONNECTING)
        {
            if (mConnectThread != null)
            {
	            mConnectThread.cancel();
	            mConnectThread = null;
            }
        }

        if (mConnectedThread != null)
        {
	        mConnectedThread.cancel();
	        mConnectedThread = null;
        }

        mConnectThread = new ConnectThread(device, secure);
        mConnectThread.start();

        setState(STATE_CONNECTING);
    }

    public synchronized void connected(BluetoothSocket socket, BluetoothDevice  device, final String socketType)
    {
        if (mConnectThread != null)
        {
	        mConnectThread.cancel();
	        mConnectThread = null;
        }

        if (mConnectedThread != null)
        {
	        mConnectedThread.cancel();
	        mConnectedThread = null;
        }

        if (mSecureAcceptThread != null)
        {
            mSecureAcceptThread.cancel();
            mSecureAcceptThread = null;
        }

	    if (mInsecureAcceptThread != null)
	    {
            mInsecureAcceptThread.cancel();
            mInsecureAcceptThread = null;
        }

        mConnectedThread = new ConnectedThread(socket, socketType);
        mConnectedThread.start();

	    Message msg = mHandler.obtainMessage(BluetoothChat.MESSAGE_DEVICE_NAME);
	    Bundle bundle = new Bundle();
	    bundle.putString(BluetoothChat.DEVICE_NAME, device.getName());
	    msg.setData(bundle);
	    mHandler.sendMessage(msg);

        setState(STATE_CONNECTED);
    }

    public synchronized void stop()
    {
        if (mConnectThread != null)
        {
            mConnectThread.cancel();
            mConnectThread = null;
        }

        if (mConnectedThread != null)
        {
            mConnectedThread.cancel();
            mConnectedThread = null;
        }

        if (mSecureAcceptThread != null)
        {
            mSecureAcceptThread.cancel();
            mSecureAcceptThread = null;
        }

        if (mInsecureAcceptThread != null)
        {
            mInsecureAcceptThread.cancel();
            mInsecureAcceptThread = null;
        }

        setState(STATE_NONE);
    }

    public void write(byte[] out)
    {
        ConnectedThread r;

        synchronized (this)
        {
            if (mState != STATE_CONNECTED)
            {
	            return;
            }

            r = mConnectedThread;
        }

        r.write(out);
    }

	public void sendAvatar(Bitmap avatar)
	{
		ConnectedThread r;

		synchronized (this)
		{
			if (mState != STATE_CONNECTED)
			{
				return;
			}

			r = mConnectedThread;
		}

		r.sendAvatar(avatar);
	}

	private void sendMessageToActivity(String message)
	{
		Message msg = mHandler.obtainMessage(BluetoothChat.MESSAGE_TOAST);
		Bundle bundle = new Bundle();
		bundle.putString(BluetoothChat.TOAST, message);
		msg.setData(bundle);
		mHandler.sendMessage(msg);
	}

    private void connectionFailed()
    {
		sendMessageToActivity("Unable to connect to device");

        BluetoothChatService.this.start();
    }

    private void connectionLost()
    {
	    sendMessageToActivity("Device connection was lost");

        BluetoothChatService.this.start();
    }

     private class AcceptThread extends Thread
    {
        private final BluetoothServerSocket mmServerSocket;
        private String mSocketType;

        public AcceptThread(boolean secure)
        {
            BluetoothServerSocket tmp = null;
            mSocketType = secure ? "Secure":"Insecure";

            try
            {
                if (secure)
                {
                    tmp = mAdapter.listenUsingRfcommWithServiceRecord(NAME_SECURE, MY_UUID_SECURE);
                }
                else
                {
                    tmp = mAdapter.listenUsingInsecureRfcommWithServiceRecord(NAME_INSECURE, MY_UUID_INSECURE);
                }
            }
            catch (IOException e)
            {
                Log.e(TAG, "Socket Type: " + mSocketType + "listen() failed", e);
            }

            mmServerSocket = tmp;
        }

        public void run()
        {
            setName("AcceptThread" + mSocketType);

            BluetoothSocket socket;

            while (mState != STATE_CONNECTED)
            {
                try
                {
                    socket = mmServerSocket.accept();
                }
                catch (IOException e)
                {
                    Log.e(TAG, "Socket Type: " + mSocketType + "accept() failed", e);
                    break;
                }

                if (socket != null)
                {
                    synchronized (BluetoothChatService.this)
                    {
                        switch (mState)
                        {
	                        case STATE_LISTEN:
	                        case STATE_CONNECTING:
	                            connected(socket, socket.getRemoteDevice(), mSocketType);
	                            break;
	                        case STATE_NONE:
	                        case STATE_CONNECTED:
	                            try
	                            {
	                                socket.close();
	                            }
	                            catch (IOException e)
	                            {
	                                Log.e(TAG, "Could not close unwanted socket", e);
	                            }
	                            break;
                        }
                    }
                }
            }
        }

        public void cancel()
        {
            try
            {
                mmServerSocket.close();
            }
            catch (IOException e)
            {
                Log.e(TAG, "Socket Type" + mSocketType + "close() of server failed", e);
            }
        }
    }

    private class ConnectThread extends Thread
    {
        private final BluetoothSocket mmSocket;
        private final BluetoothDevice mmDevice;
        private String mSocketType;

        public ConnectThread(BluetoothDevice device, boolean secure)
        {
            mmDevice = device;
            BluetoothSocket tmp = null;
            mSocketType = secure ? "Secure" : "Insecure";

            try
            {
                if (secure)
                {
                    tmp = device.createRfcommSocketToServiceRecord(MY_UUID_SECURE);
                }
                else
                {
                    tmp = device.createInsecureRfcommSocketToServiceRecord(MY_UUID_INSECURE);
                }
            }
            catch (IOException e)
            {
                Log.e(TAG, "Socket Type: " + mSocketType + "create() failed", e);
            }

            mmSocket = tmp;
        }

        public void run()
        {
            Log.i(TAG, "BEGIN mConnectThread SocketType:" + mSocketType);

            setName("ConnectThread" + mSocketType);

            mAdapter.cancelDiscovery();

            try
            {
                mmSocket.connect();
            }
            catch (IOException e)
            {
                try
                {
                    mmSocket.close();
                }
                catch (IOException e2)
                {
                    Log.e(TAG, "unable to close() " + mSocketType + " socket during connection failure", e2);
                }

                connectionFailed();

                return;
            }

            synchronized (BluetoothChatService.this)
            {
                mConnectThread = null;
            }

            connected(mmSocket, mmDevice, mSocketType);
        }

        public void cancel()
        {
            try
            {
                mmSocket.close();
            }
            catch (IOException e)
            {
                Log.e(TAG, "close() of connect " + mSocketType + " socket failed", e);
            }
        }
    }

    private class ConnectedThread extends Thread
    {
        private final BluetoothSocket mmSocket;
        private final InputStream mmInStream;
        private final OutputStream mmOutStream;

        public ConnectedThread(BluetoothSocket socket, String socketType)
        {
            Log.d(TAG, "create ConnectedThread: " + socketType);

            mmSocket = socket;
            InputStream tmpIn = null;
            OutputStream tmpOut = null;

            try
            {
                tmpIn = socket.getInputStream();
                tmpOut = socket.getOutputStream();
            }
            catch (IOException e)
            {
                Log.e(TAG, "temp sockets not created", e);
            }

            mmInStream = tmpIn;
            mmOutStream = tmpOut;
        }

        public void run()
        {
            Log.i(TAG, "BEGIN mConnectedThread");

            try
	        {
		        byte[] buffer = new byte[1024];

		        int bytes;

		        int avatarLength = mmInStream.read() << 24 |
				        (mmInStream.read() & 0xFF) << 16 |
				        (mmInStream.read() & 0xFF) << 8 |
				        (mmInStream.read() & 0xFF);

		        byte[] avatarBuffer = new byte[avatarLength];
		        int avatarEnd = 0;

		        while (avatarEnd != avatarLength)
		        {
			        bytes = mmInStream.read(avatarBuffer, avatarEnd, avatarLength - avatarEnd);

			        avatarEnd += bytes;
		        }

		        mHandler.obtainMessage(BluetoothChat.MESSAGE_AVATAR, avatarLength, -1, avatarBuffer).sendToTarget();

	            while (true)
	            {
                    bytes = mmInStream.read(buffer);

                    mHandler.obtainMessage(BluetoothChat.MESSAGE_READ, bytes, -1, buffer).sendToTarget();
	            }
	        }
	        catch (Throwable e)
	        {
		        Log.e(TAG, "disconnected" + e.getMessage(), e);
		        connectionLost();

		        BluetoothChatService.this.start();
	        }
        }

        public void write(byte[] buffer)
        {
            try
            {
                mmOutStream.write(buffer);

                mHandler.obtainMessage(BluetoothChat.MESSAGE_WRITE, -1, -1, buffer).sendToTarget();
            }
            catch (IOException e)
            {
                Log.e(TAG, "Exception during write", e);
            }
        }

	    public void sendAvatar(Bitmap avatar)
	    {
		    final ByteArrayOutputStream stream = new ByteArrayOutputStream();
		    avatar.compress(Bitmap.CompressFormat.PNG, 100, stream);
		    final byte[] imageByteArray = stream.toByteArray();

		    try
		    {
			    mmOutStream.write(new byte[]{
					    (byte)(imageByteArray.length >> 24),
					    (byte)(imageByteArray.length >> 16),
					    (byte)(imageByteArray.length >> 8),
					    (byte)(imageByteArray.length),
			    });

			    mmOutStream.write(imageByteArray);
		    }
		    catch (IOException e)
		    {
			    Log.e(TAG, "Exception during write", e);
		    }
	    }

        public void cancel()
        {
            try
            {
                mmSocket.close();
            }
            catch (IOException e)
            {
                Log.e(TAG, "close() of connect socket failed", e);
            }
        }
    }
}