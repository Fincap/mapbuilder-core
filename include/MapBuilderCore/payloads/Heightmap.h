#pragma once
#include "MapBuilderCore\Payload.h"

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

    ~Heightmap()
    {
      delete[] points;
    }
  };
}
