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
    // Value stores the RBGA colour 0xRRGGBBAA (Alpha not used)
    std::map<unsigned char, uint32_t> colourRanges;

  };
}
