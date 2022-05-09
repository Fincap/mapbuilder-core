#pragma once
#include "..\APIExport.h"

#include <fstream>
#include <iostream>

#include "..\core\Module.h"
#include "..\payloads\Heightmap.h"

namespace mbc
{
  class MAPBUILDER_API HeightmapOut : public Module
  {
  public:
    HeightmapOut();

    // Inherit from base class - must be implemented
    std::vector<std::type_index> registerTypes(PayloadFactory&) override;
    bool processPayloads(PayloadTypeMap) override;

    // Processing parameters
    const char* outputFilepath;

  };
}