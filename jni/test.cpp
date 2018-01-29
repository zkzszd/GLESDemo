#include <stdlib.h>
#include <stdio.h>
#include "test.h"
#include "YUVUtil.hpp"
#include "NativeYUVSurface.h"

using namespace WeiYu;

static JavaVM* g_jvm = NULL;
static NativeYUVSurface* nativeYUVSurface = NULL;

extern "C"
{
    JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void *reserved)
    {
        JNIEnv* env = NULL;
        jint result = -1;

        if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
            return -1;

        g_jvm = vm;

        return JNI_VERSION_1_4;
    }


    JNIEXPORT void JNICALL Java_zkzszd_opengl_GL2JNILib_init
    (JNIEnv *env, jclass oclass, jobject glSurface)
    {
        if (nativeYUVSurface)
        {
            WEBRTC_TRACE(kTraceInfo, kTraceVideoRenderer, -1, "初期化失败[%d].", __LINE__);
            return;
        }

        nativeYUVSurface = new NativeYUVSurface(g_jvm, glSurface);
        if (nativeYUVSurface->Init() != 0)
        {
            WEBRTC_TRACE(kTraceInfo, kTraceVideoRenderer, -1, "初期化失败[%d].", __LINE__);
            return;
        }
    }

    JNIEXPORT void JNICALL Java_zkzszd_opengl_GL2JNILib_putCameraData(JNIEnv* env,
            jclass clazz,jint jwidth, jint jheight, jbyteArray jyuv_data)
    {
    	int total = jwidth*jheight*3/2;
    	jbyte* pdata = env->GetByteArrayElements(jyuv_data, 0);




//    	uint8_t *buffOut = NULL;
//		int outSize = 0;
//		nativeYUVSurface->GetDataBuf(buffOut, outSize);
//
//		memcpy(buffOut,pdata,total);
//
//		nativeYUVSurface->DeliverFrame(jwidth, jheight);

    	//此处是旋转后的数据，所以直接初始化宽高颠倒
    	YUVStruct *yuvData = new YUVStruct(total,jheight,jwidth);
    	YUVUtil::YUV420spRotateNegative90(yuvData->data,(char*)pdata,jwidth,jheight);

    	nativeYUVSurface->PutNV12DataAndRender((uint8_t*)yuvData->data,total,yuvData->width,yuvData->height);
    	delete yuvData;

    	env->ReleaseByteArrayElements(jyuv_data, pdata, 0);
    }

    JNIEXPORT void JNICALL Java_zkzszd_opengl_GL2JNILib_destory(JNIEnv* env,
                jclass clazz)
    {
    	delete nativeYUVSurface;
    }

}
