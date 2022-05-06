#include "Pipeline.h"

namespace mbc
{
  bool Pipeline::execute()
  {
    
    for (int stage = 0; stage < NUM_STAGES; stage++)
    {
      for (int module = 0; module < modules_[stage].size(); module++)
      {
        modules_[stage][module]->processPayloads(payloads_);
      }
    }

    return false;
  }

  bool Pipeline::addModule(ModulePtr newModule)
  {
    /*
    1. Check generation stage of module and add to appropriate list.
    2. Iterate through input and output types of module and add new
      types to payloads_
    */

    int newModuleStage = (int) newModule->getPipelineStage();

    // Register module to modules list
    if (newModuleStage < 0 || newModuleStage >= NUM_STAGES)
    {
      std::cerr << "Invalid PipelineStage for " << std::type_index(typeid(newModule)).name() << std::endl;
      return false;
    }
    else
    {
      modules_[newModuleStage].push_back(newModule);
    }

    // Register module's payloads with payload factory
    newModule->registerTypes(payloadFactory_);

    // Check for any uninstantiated payloads in module's inputs.
    for (auto type : newModule->getInputTypes())
    {
      // If key doesn't already exist in payloads map: create it
      if (payloads_.count(type) == 0)
      {
        payloads_[type] = payloadFactory_.createPayload(type);
      }
    }

    // Exact same as above, but for module's outputs.
    for (auto type : newModule->getOutputTypes())
    {
      // If key doesn't already exist in payloads map: create it
      if (payloads_.count(type) == 0)
      {
        payloads_[type] = payloadFactory_.createPayload(type);
      }
    }

#ifdef _DEBUG
    std::cout << "Payloads after: " << payloads_.size() << std::endl;
    
    for (int i = 0; i < NUM_STAGES; i++)
    {
      std::cout << "Stage " << i + 1 << ": " << modules_[i].size() << " modules" << std::endl;
    }

    std::cout << std::endl;
#endif

    return true;
  }
}
