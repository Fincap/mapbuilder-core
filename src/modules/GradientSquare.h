#pragma once
#include "APIExport.h"

#include <algorithm>

#include "core\Module.h"
#include "payloads\Heightmap.h"
#include "util\ModuleHelpers.h"

namespace mbc
{
  /*
  Applies a square-shaped gradient to the Heightmap, forcing the borders of the
  map to have a height of 0, resulting in an island map.
  */
  class MAPBUILDER_API GradientSquare : public Module
  {
  public:
    GradientSquare();

    // Inherit from base class - must be implemented
    TypeIndexVector registerTypes(PayloadFactory&) override;
    bool processPayloads(const PayloadTypeMap&) override;

    // Processing parameters
    double fullness, size;

  private:
    // Gradient generator method
    std::vector<double> generateGradient(int, int);
  };
}