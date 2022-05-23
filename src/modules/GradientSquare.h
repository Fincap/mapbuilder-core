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

    bool operator==(Module::Ptr) override;
    bool operator!=(Module::Ptr) override;

    // Processing parameters
    double fullness, size;

  private:
    // Gradient generator method
    std::vector<double> generateGradient(int, int);
  };
}


// Inline definitions for operator overloads
inline bool mbc::GradientSquare::operator==(Module::Ptr other)
{
  auto castOther = std::dynamic_pointer_cast<GradientSquare>(other);
  if (castOther)
  {
    return (fullness == castOther->fullness
      && size == castOther->size);
  }  // Return false if other cannot be cast to this Module.

  return false;
}


inline bool mbc::GradientSquare::operator!=(Module::Ptr other)
{
  return !(this->operator==(other));
}
