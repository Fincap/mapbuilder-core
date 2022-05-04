#pragma once
#include "..\core\Payload.h"

namespace mbc
{
  struct Heightmap : public Payload
  {
    int width, height;
    unsigned char* points;
  };
}
