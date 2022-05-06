#pragma once
#include "..\core\Payload.h"

namespace mbc
{
  struct Heightmap : public Payload
  {
    int width, height;
    unsigned char* points;

    std::unordered_map<std::string, std::any> getValues() override;
  };

  inline std::unordered_map<std::string, std::any> Heightmap::getValues()
  {
    std::unordered_map<std::string, std::any> values;
    values["width"] = width;
    values["height"] = height;
    values["points"] = points;

    return values;
  }
}
