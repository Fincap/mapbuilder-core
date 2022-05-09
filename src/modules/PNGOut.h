#pragma once
#include "..\APIExport.h"

#include <iostream>

#include <png++/png.hpp>

#include "..\core\Module.h"
#include "..\payloads\ColouredHeightmap.h"

namespace mbc
{
  class MAPBUILDER_API PNGOut : public Module
  {
  public:
    PNGOut();

    // Inherit from base class - must be implemented
    std::vector<std::type_index> registerTypes(PayloadFactory&) override;
    bool processPayloads(PayloadTypeMap) override;

    // Processing parameters
    const char* outputFilepath;

  };
}