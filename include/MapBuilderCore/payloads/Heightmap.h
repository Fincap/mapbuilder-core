#pragma once
#include "core\Payload.h"

namespace mbc
{
  /*
  Payload storing 1D array of unsigned chars representing a map's
  height values.
  */
  struct Heightmap : public Payload
  {
    int width, height;
    unsigned char* points;
  };
}
