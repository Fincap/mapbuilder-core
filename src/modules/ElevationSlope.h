#pragma once
#include "APIExport.h"

#include "core\Module.h"
#include "payloads\Heightmap.h"

namespace mbc
{
  class MAPBUILDER_API ElevationSlope : public Module
  {
  public:
    ElevationSlope();

    // Inherit from base class - must be implemented
    std::vector<std::type_index> registerTypes(PayloadFactory&) override;
    bool processPayloads(PayloadTypeMap) override;

    // Processing parameters
    double slope;
  };
}