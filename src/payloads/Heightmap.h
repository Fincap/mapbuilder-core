#pragma once
#include "..\core\Payload.h"

namespace mbc
{
  struct Heightmap : public Payload
  {
    int width, height;
    unsigned char* points;

    PayloadValues unpack();
  };

  inline PayloadValues Heightmap::unpack()
  {
    std::unordered_map<std::string, std::any> values;
    values["width"] = width;
    values["height"] = height;
    values["points"] = points;

    return values;
  }
}
