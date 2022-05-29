#pragma once

#include <vector>
#include <typeindex>

#include "MapBuilderCore\APIExport.h"
#include "MapBuilderCore\Module.h"
#include "MapBuilderCore\PipelineStage.h"
#include "MapBuilderCore\payloads\Heightmap.h"
#include "MapBuilderCore\util\ModuleHelpers.h"

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
    Canvas::Ptr clone() const override;

    // Inherit from base class - must be implemented
    TypeIndexVector registerTypes(PayloadFactory&) override;
    bool processPayloads(const PayloadTypeMap&) override;

    bool operator==(Module::Ptr) override;
    bool operator!=(Module::Ptr) override;

    // Processing parameters
    int width, height;

    // Serialize module
    template<typename Archive>
    void serialize(Archive& archive);

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


template<typename Archive>
inline void mbc::Canvas::serialize(Archive& archive)
{
  archive(
    CEREAL_NVP(width),
    CEREAL_NVP(height)
  );
}


CEREAL_REGISTER_TYPE(mbc::Canvas);
CEREAL_REGISTER_POLYMORPHIC_RELATION(mbc::Module, mbc::Canvas);
