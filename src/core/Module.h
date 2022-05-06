#pragma once
#include <vector>
#include <typeindex>
#include <memory>

#include "PipelineStage.h"
#include "Payload.h"

namespace mbc
{
  class Module
  {
  public:
    Module(PipelineStage);

    virtual std::vector<std::type_index> getInputTypes() = 0;
    virtual std::vector<std::type_index> getOutputTypes() = 0;
    
    virtual bool processPayloads(PayloadTypeMap) = 0;

    virtual PipelineStage getPipelineStage() final;

  protected:
    const PipelineStage PIPELINE_STAGE;

  };

  // Inline definition of default constructor - to be called by derived class
  inline Module::Module(PipelineStage stage) :
    PIPELINE_STAGE(stage)
  {}

  // Inline definition to preserve runtime mutability of PipelineStage
  inline PipelineStage Module::getPipelineStage()
  {
    return PIPELINE_STAGE;
  }

  // Convenience typing
  using ModulePtr = std::shared_ptr<Module>;

}