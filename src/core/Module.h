#pragma once
#include <vector>
#include <typeindex>

#include "PipelineStage.h"

namespace mbc
{
  class Module
  {
  public:
    virtual std::vector<std::type_index> getInputTypes() = 0;
    virtual std::vector<std::type_index> getOutputTypes() = 0;
    
    virtual PipelineStage getPipelineStage() final;

  protected:
    const PipelineStage PIPELINE_STAGE;

  };

  // Inline definition to preserve runtime mutability of PipelineStage
  inline PipelineStage Module::getPipelineStage()
  {
    return PIPELINE_STAGE;
  }

}