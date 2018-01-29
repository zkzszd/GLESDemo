package zkzszd.opengl;

import zkzszd.opengl.EFCameraView.EFCameraViewListener;

import com.example.geesdemo.R;

import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.SurfaceView;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.WindowManager.LayoutParams;
import android.widget.Button;

public class MainActivity extends Activity {

	EFCameraView camera_view;
	private SurfaceView  mView = null;  
	private Button bt_open;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		camera_view = (EFCameraView) findViewById(R.id.camera_view);
		mView  = (SurfaceView) findViewById(R.id.sv_native);
		//mView = ViERenderer.CreateRenderer(this, true);  

		GL2JNILib.init(mView);  
		bt_open = (Button) findViewById(R.id.bt_open);
		bt_open.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				
					camera_view.OpenCamera();
					camera_view.pausePreview();

			}
		});
		camera_view.setCameraListenrer(new EFCameraViewListener() {
			
			@Override
			public void onCameraPreviewFrame(int width, int height, byte[] data,
					int format) 
			{
				byte[] nv12 = new byte[(int) (width*height*1.5)];
				
				//NV21ToYUV420(data,nv12,width,height);
				
				NV21ToNV12(data,nv12,width,height);
				
				GL2JNILib.putCameraData(width,height,nv12);
			}
		});
		
	}
	@Override
	protected void onRestart() {
		// TODO Auto-generated method stub
		super.onRestart();
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
	
	private void NV21ToNV12(byte[] nv21,byte[] nv12,int width,int height){
		if(nv21 == null || nv12 == null)return;
		int framesize = width*height;
		int i = 0,j = 0;
		System.arraycopy(nv21, 0, nv12, 0, framesize);
		for(i = 0; i < framesize; i++){
			nv12[i] = nv21[i];
		}
		for (j = 0; j < framesize/2; j+=2)
		{
		 nv12[framesize + j-1] = nv21[j+framesize];
		}
		for (j = 0; j < framesize/2; j+=2)
		{
		 nv12[framesize + j] = nv21[j+framesize-1];
		}
	}
	
	private void NV21ToYUV420(byte[] nv21,byte[] yuv420,int width, int height)
	{
		if(nv21 == null || yuv420 == null)return;
		int framesize = width*height;
		int i = 0,j = 0;
		System.arraycopy(nv21, 0, yuv420, 0, framesize);
		for(i = 0;i<framesize/4;i++)
		{
			yuv420[framesize+framesize/4+i] = nv21[i*2+framesize];
		}
		for (j = 0; j < framesize/4; j++)
		{
			yuv420[framesize + j] = nv21[j*2+1+framesize];
		}
	}
}
