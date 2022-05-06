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
    std::cout << "Payloads before: " << payloads_.size() << std::endl;

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

    for (auto type : newModule->getInputTypes())
    {
      // If key doesn't already exist in payloads map: add it
      if (payloads_.count(type) == 0)
      {
        payloads_[type] = payloadFactory_.createPayload(type);
      }
    }

    for (auto type : newModule->getOutputTypes())
    {
      // If key doesn't already exist in payloads map: add it
      if (payloads_.count(type) == 0)
      {
        payloads_[type] = payloadFactory_.createPayload(type);
      }
    }

    std::cout << "Payloads after: " << payloads_.size() << std::endl;

    return true;
  }

  void Pipeline::registerPayload(std::type_index typeIndex, PayloadFactory::PayloadCreatePtr payloadCreatePtr)
  {
    payloadFactory_.registerPayload(typeIndex, payloadCreatePtr);
  }
}
