#pragma once
#ifdef MAPBUILDER_EXPORTS
#define MAPBUILDER_API __declspec(dllexport)
#else
#define MAPBUILDER_API __declspec(dllimport)
#endif

#include "..\core\Module.h"
#include "..\payloads\Heightmap.h"

namespace mbc
{
  class MAPBUILDER_API ElevationSlope : public Module
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