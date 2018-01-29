#include "MyDef.hpp"

namespace WeiYu
{
  YUVStruct::~YUVStruct()
  {
    if(data)
    {
      free(data);
    }
  }
  YUVStruct::YUVStruct(char*data,int32 size,int32 width,int32 height)
  :size(size),width(width),height(height)
  {
    this->data = (char*)malloc(size);
    memcpy(this->data,data,size);
  }

  YUVStruct::YUVStruct(int32 size,int32 width,int32 height)
  :size(size),width(width),height(height)
  {
    this->data = (char*)malloc(size);
  }

  YUV420p::YUV420p(int32 size,int32 width,int height):YUVStruct(size,width,height)
  {
    int frame = width*height;
    Y = data;
    U = data + frame;
    V = data + frame*5/4;
  }
  YUV420p::YUV420p(char*data,int32 size,int32 width,int height):YUVStruct(data,size,width,height)
  {
    int frame = width*height;
    Y = data;
    U = data + frame;
    V = data + frame*5/4;
  }
  YUV420p::~YUV420p()
  {

  }

}
