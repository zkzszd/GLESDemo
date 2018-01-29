package zkzszd.opengl;
/** 
 * @author  zkzszd E-mail:lnb@love.com
 * @date 创建时间：2017-12-8 下午4:59:37 
 * @version 1.0 
 * @parameter  
 * @since  
 * @return  
 */
public class GL2JNILib {
	static {    
        System.loadLibrary("MICloudPub");  
    }    
      
   /**  
    */    
    public static native void init(Object glSurface);  
    public static native void putCameraData(int jwidth, int jheight, byte[] jyuv_data);
}
