#pragma once
#include "APIExport.h"

#include <fstream>
#include <iostream>
#include <filesystem>

#include "core\Module.h"
#include "payloads\Heightmap.h"
#include "util\OutputValidation.h"
#include "util\ModuleHelpers.h"

namespace mbc
{
  /*
  Module that writes the Heightmap to a proprietary binary file format (.hmp),
  where the first 64 bits are the map's width (32 bit) and height (32 bit), and
  the remainder of the file is each height value (1 height value per byte).
  */
  class MAPBUILDER_API HeightmapOut : public Module
  {
  public:
    HeightmapOut();

    // Inherit from base class - must be implemented
    TypeIndexVector registerTypes(PayloadFactory&) override;
    bool processPayloads(const PayloadTypeMap&) override;

    // Processing parameters
    char* outputFilepath;

  };
}