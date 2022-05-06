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
    1. Check generation stage of module and add to appropriate list.
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
      std::cerr << "Invalid PipelineStage for " << std::type_index(typeid(newModule)).name() << std::endl;
      return false;

    }

    // Check for new payloads in module inputs and attempt to register them.
    for (auto type : newModule->getInputTypes())
    {
      // If key doesn't already exist in payloads map: add it
      if (payloads_.count(type) == 0)
      {
        // If key isn't in payloadFactory, return false
        // (This will usually be caused by a payload not being registered)
        PayloadPtr newPayload = payloadFactory_.createPayload(type);
        if (newPayload == nullptr)
        {
          std::cerr << "Null pointer returned when trying to create input payload " << type.name() << std::endl;
          return false;
        }

        payloads_[type] = payloadFactory_.createPayload(type);
      }
    }

    // Exact same as above, but for module's outputs.
    for (auto type : newModule->getOutputTypes())
    {
      if (payloads_.count(type) == 0)
      {
        PayloadPtr newPayload = payloadFactory_.createPayload(type);
        if (newPayload == nullptr)
        {
          std::cerr << "Null pointer returned when trying to create output payload " << type.name() << std::endl;
          return false;
        }

        payloads_[type] = payloadFactory_.createPayload(type);
      }
    }

    std::cout << "Payloads after: " << payloads_.size() << std::endl;

    return true;
  }
}
