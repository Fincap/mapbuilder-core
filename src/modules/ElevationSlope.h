#pragma once

#include "..\core\Module.h"
#include "..\payloads\Heightmap.h"

namespace mbc
{
  class ElevationSlope : public Module
  {
  public:
    ElevationSlope();

    // Inherit from base class - must be implemented
    std::vector<std::type_index> registerTypes(PayloadFactory&) override;
    bool processPayloads(PayloadTypeMap) override;

  private:
    // Processing parameters
    double slope_;
  };
}