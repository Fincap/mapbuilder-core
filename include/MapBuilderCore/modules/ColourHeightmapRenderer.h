#pragma once

#include <vector>
#include <typeindex>
#include <map>

#include "MapBuilderCore\APIExport.h"
#include "MapBuilderCore\Module.h"
#include "MapBuilderCore\PipelineStage.h"
#include "MapBuilderCore\payloads\ColourSetPayload.h"
#include "MapBuilderCore\payloads\ColouredHeightmap.h"
#include "MapBuilderCore\payloads\Heightmap.h"
#include "MapBuilderCore\util\ModuleHelpers.h"

namespace mbc
{
  /*
  Module that applies the ColourSet payload to the Heightmap to produce a
  ColouredHeightmap, colouring each point on the Heightmap according to the
  colours defined in the ColourSet.
  */
  class MAPBUILDER_API ColourHeightmapRenderer : public Module
  {
  public:
    ColourHeightmapRenderer();
    ColourHeightmapRenderer::Ptr clone() const override;

    // Inherit from base class - must be implemented
    TypeIndexVector registerTypes(PayloadFactory&) override;
    bool processPayloads(const PayloadTypeMap&) override;

    bool operator==(Module::Ptr) override;
    bool operator!=(Module::Ptr) override;

    // Serialize module
    template<typename Archive>
    void serialize(Archive& archive);

  };
}


// Inline definitions for operator overloads
inline bool mbc::ColourHeightmapRenderer::operator==(Module::Ptr other)
{
  auto castOther = std::dynamic_pointer_cast<ColourHeightmapRenderer>(other);
  // As there are no processing parameters, assume equality if both Modules are
  // of the same type.
  return (bool) castOther;
}


inline bool mbc::ColourHeightmapRenderer::operator!=(Module::Ptr other)
{
  return !(this->operator==(other));
}


template<typename Archive>
inline void mbc::ColourHeightmapRenderer::serialize(Archive& archive)
{
  // No parameters to serialize
}


CEREAL_REGISTER_TYPE(mbc::ColourHeightmapRenderer);
CEREAL_REGISTER_POLYMORPHIC_RELATION(mbc::Module, mbc::ColourHeightmapRenderer);
