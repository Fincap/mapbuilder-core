#pragma once
#include "APIExport.h"

#include "core\Module.h"
#include "payloads\Heightmap.h"
#include "util\ModuleHelpers.h"

namespace mbc
{
  /*
  Module that applies a slope to the generated Heightmap by raising each value
  in the Heightmap to the power of the given elevation slope factor.
  */
  class MAPBUILDER_API ElevationSlope : public Module
  {
  public:
    ElevationSlope();

    // Inherit from base class - must be implemented
    TypeIndexVector registerTypes(PayloadFactory&) override;
    bool processPayloads(const PayloadTypeMap&) override;

    // Processing parameters
    double slope;
  };
}