#pragma once
#include "APIExport.h"

#include <vector>
#include <typeindex>
#include <map>

#include "core\Module.h"
#include "core\PipelineStage.h"
#include "payloads\ColourSetPayload.h"
#include "payloads\ColouredHeightmap.h"
#include "payloads\Heightmap.h"
#include "util\ModuleHelpers.h"

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
