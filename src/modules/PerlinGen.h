#pragma once
#include "APIExport.h"

#include <vector>
#include <typeindex>

#include "PerlinNoise.h"

#include "core\Module.h"
#include "payloads\Heightmap.h"
#include "util\ModuleHelpers.h"

namespace mbc
{
  class MAPBUILDER_API PerlinGen : public Module
  {
  public:
    PerlinGen();

    // Inherit from base class - must be implemented
    std::vector<std::type_index> registerTypes(PayloadFactory&) override;
    bool processPayloads(PayloadTypeMap) override;

    // Processing parameters
    uint32_t seed;
    double frequency;
    uint32_t octaves;

  };
}