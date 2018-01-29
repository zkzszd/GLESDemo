//
//  MyTypedef.h
//  
//
//  Created by zkzszd on 2017/4/25.
//
//

#ifndef MyTypedef_h
#define MyTypedef_h
#include <stdlib.h>
#include <string.h>

namespace WeiYu {
    typedef unsigned char       uint8;
    typedef char                int8;
    typedef unsigned short      uint16;
    typedef short               int16;
    typedef unsigned int        uint32;
    typedef int                 int32;
    typedef unsigned long long  uint64;
    typedef long long           int64;

#define ABS(a) ((a)<(0)?(-a):(a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))
	
#define CODE_FAIL -1
#define CODE_SUCESS 0
#define CODE_FILE_OPEN_FILE 1

      enum RET_CODE
      {
              RET_ERR_UNKNOWN = -2,
              RET_FAIL = -1,							//ʧ��
              RET_OK	= 0,							//�ɹ�
              RET_ERR_OPEN_FILE,						//���ļ�ʧ�ܣ������ļ�������
              RET_ERR_NOT_SUPPORT,					//��֧�ֵĲ���
              RET_ERR_OUTOFMEMORY,					//	�ڴ����
              RET_ERR_STACKOVERFLOW,					//	��ջ���
              RET_ERR_NULLREFERENCE,					//	������
              RET_ERR_ARGUMENTOUTOFRANGE,				//	��������������Χ��
              RET_ERR_PARAMISMATCH,					//	������ƥ�� ��������
      };

      struct YUVStruct
      {
        int32 size = 0;
        int32 width = 0;
        int32 height = 0;
        char *data = NULL;
        YUVStruct(int32 size,int32 width,int height);
        YUVStruct(char*data,int32 size,int32 width,int height);
        virtual ~YUVStruct();
      };
      //NV12: YYYYYYYY UVUV
      typedef YUVStruct YUVNV12;
      //NV21: YYYYYYYY VUVU
      typedef YUVStruct YUVNV21;

      struct YUV420p : public YUVStruct
      {
        char* Y;
        char* U;
        char* V;

        YUV420p(int32 size,int32 width,int height);
        YUV420p(char*data,int32 size,int32 width,int height);
        virtual ~YUV420p();
      };
}

#endif /* MyTypedef_h */
