#pragma once

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
    std::vector<std::type_index> getInputTypes() override;
    std::vector<std::type_index> getOutputTypes() override;
    PayloadTypeMap processPayloads(PayloadTypeMap) override;

    // Processing parameters
    int width, height;

  };
}