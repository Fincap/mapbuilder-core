#pragma once
#include "APIExport.h"

#include <vector>
#include <typeindex>

#include "core\Module.h"
#include "core\PipelineStage.h"
#include "payloads\Heightmap.h"
#include "util\ModuleHelpers.h"

namespace mbc
{
  /*
  Module that generates a blank Heightmap payload of the given width and
  height. This Module should be implemented by all Pipelines, and should be
  added first.
  */
  class MAPBUILDER_API Canvas : public Module
  {
  public:
    Canvas();

    // Inherit from base class - must be implemented
    TypeIndexVector registerTypes(PayloadFactory&) override;
    bool processPayloads(const PayloadTypeMap&) override;

    bool operator==(Module::Ptr) override;
    bool operator!=(Module::Ptr) override;

    // Processing parameters
    int width, height;

  };
}


// Inline definitions for operator overloads
inline bool mbc::Canvas::operator==(Module::Ptr other)
{
  auto castOther = std::dynamic_pointer_cast<Canvas>(other);
  if (castOther)
  {
    return (width == castOther->width
      && height == castOther->height);
  }  // Return false if other cannot be cast to this Module.

  return false;
}


inline bool mbc::Canvas::operator!=(Module::Ptr other)
{
  return !(this->operator==(other));
}
