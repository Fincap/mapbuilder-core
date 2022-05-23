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

  };
}