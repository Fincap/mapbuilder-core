#pragma once
#include <map>

#include "..\core\Payload.h"

namespace mbc
{
  struct ColourSetPayload : public Payload
  {
    // A set of ranges (0-50, 51-70, 71-100, etc)
    // Each range has a corresponding RGB
    // Key stores the max value in the range.
    // Value stores the RBG colour 0xRRGGBB
    std::map<unsigned char, uint32_t> colourRanges;

  };
}
