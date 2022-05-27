#pragma once
#include <map>

#include "MapBuilderCore\Payload.h"

namespace mbc
{
  /*
  Payload storing a "rasterized" image of the generated map, based
  on the combination of the Heightmap and ColourSet payloads.
  */
  struct ColouredHeightmap : public Payload
  {
    int width, height;
    uint32_t* colouredPoints;

  };
}
