#pragma once
#include "..\APIExport.h"

#include <vector>
#include <typeindex>
#include <memory>

#include "PipelineStage.h"
#include "Payload.h"
#include "PayloadFactory.h"

namespace mbc
{
  class MAPBUILDER_API Module
  {
  public:
    Module(PipelineStage);

    // This function registers all types with the linked factory, and returns a list of
    // any types that were newly registered so they can be instantiated.
    virtual std::vector<std::type_index> registerTypes(PayloadFactory&) = 0;    

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