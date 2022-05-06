#pragma once
#include <vector>
#include <typeindex>

#include "..\core\Module.h"
#include "..\core\PipelineStage.h"
#include "..\payloads\Heightmap.h"

namespace mbc
{
  class Canvas : public Module
  {
  public:
    Canvas();

    // Inherit from base class - must be implemented
    std::vector<std::type_index> registerTypes(PayloadFactory&) override;
    bool processPayloads(PayloadTypeMap) override;

    // Processing parameters
    int width, height;

  };
}