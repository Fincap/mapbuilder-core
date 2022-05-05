#include "Pipeline.h"

namespace mbc
{
  bool Pipeline::execute()
  {
    // TODO implement
    return false;
  }

  bool Pipeline::addModule(ModulePtr newModule)
  {
    /*
    1. Check generation stage of module and add to appropriate list
    2. Iterate through input and output types of module and add new
      types to payloads_
    */
    switch (newModule->getPipelineStage())
    {
    case PipelineStage::GENERATION:
      generationModules_.push_back(newModule);
      break;

    case PipelineStage::MANIPULATION:
      manipulationModules_.push_back(newModule);
      break;

    case PipelineStage::RENDER:
      renderModules_.push_back(newModule);
      break;

    case PipelineStage::OUTPUT:
      outputModules_.push_back(newModule);
      break;

    default:
      return false;

    }

    for (auto type : newModule->getInputTypes())
    {
      // If key doesn't already exist in payloads map: add it
      if (payloads_.count(type) == 0)
      {
        // TODO implement
        // This will most likely require the creation of Payload factories
      }
    }

    return true;
  }
}