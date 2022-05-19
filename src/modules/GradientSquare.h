#pragma once
#include "APIExport.h"

#include <algorithm>

#include "core\Module.h"
#include "payloads\Heightmap.h"
#include "util\ModuleHelpers.h"

namespace mbc
{
  class MAPBUILDER_API GradientSquare : public Module
  {
  public:
    GradientSquare();

    // Inherit from base class - must be implemented
    std::vector<std::type_index> registerTypes(PayloadFactory&) override;
    bool processPayloads(PayloadTypeMap) override;

    // Processing parameters
    double fullness, size;

  private:
    // Gradient generator method
    std::vector<double> generateGradient(int, int);
  };
}