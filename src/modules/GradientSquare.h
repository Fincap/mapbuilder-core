#pragma once
#ifdef MAPBUILDER_EXPORTS
#define MAPBUILDER_API __declspec(dllexport)
#else
#define MAPBUILDER_API __declspec(dllimport)
#endif

#include <algorithm>

#include "..\core\Module.h"
#include "..\payloads\Heightmap.h"

namespace mbc
{
  class MAPBUILDER_API GradientSquare : public Module
  {
  public:
    GradientSquare();

    // Inherit from base class - must be implemented
    std::vector<std::type_index> registerTypes(PayloadFactory&) override;
    bool processPayloads(PayloadTypeMap) override;

  private:
    // Processing parameters
    double fullness_, size_;

    // Gradient generator method
    std::vector<double> generateGradient(int, int);
  };
}