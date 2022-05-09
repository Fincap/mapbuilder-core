#pragma once
#include "..\APIExport.h"

#include <vector>
#include <typeindex>
#include <map>

#include "..\core\Module.h"
#include "..\core\PipelineStage.h"
#include "..\payloads\ColourSetPayload.h"
#include "..\payloads\ColouredHeightmap.h"
#include "..\payloads\Heightmap.h"

namespace mbc
{
  // Module that applies the ColourSet payload to the Heightmap
  // to produce a ColouredHeightmap.
  class MAPBUILDER_API ColourHeightmapRenderer : public Module
  {
  public:
    ColourHeightmapRenderer();

    // Inherit from base class - must be implemented
    TypeIndexVector registerTypes(PayloadFactory&) override;
    bool processPayloads(PayloadTypeMap) override;

  };
}