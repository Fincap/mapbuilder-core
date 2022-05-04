#pragma once

#include "..\core\Module.h"
#include "..\core\PipelineStage.h"

namespace mbc
{
  class Canvas : public Module
  {
  public:
    Canvas();

    std::vector<std::type_index> getInputTypes() override;
    std::vector<std::type_index> getOutputTypes() override;

    PayloadTypeMap processPayloads(PayloadTypeMap) override;

  };
}