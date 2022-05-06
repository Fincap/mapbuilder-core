#pragma once
#include "..\core\Payload.h"

namespace mbc
{
  struct Heightmap : public Payload
  {
    int width, height;
    unsigned char* points;

    PayloadValues unpack() override;
  };

  inline PayloadValues Heightmap::unpack()
  {
    PayloadValues values;
    values["width"] = width;
    values["height"] = height;
    values["points"] = points;

    return values;
  }
}
