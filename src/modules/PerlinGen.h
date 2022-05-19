#pragma once
#include "APIExport.h"

#include <vector>
#include <typeindex>
#include <future>

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

  /* Function to be called asynchronously to compute the 2D perlin grid in
    parallel. */
  void computePerlinGrid(unsigned char* begin, unsigned char* end,
    const double& fx, const double& fy, const uint32_t& oct,
    const int& startIndex, const int& width, const uint32_t& seed);
}