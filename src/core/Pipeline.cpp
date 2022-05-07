#include "Pipeline.h"

namespace mbc
{
  Pipeline::Pipeline()
  {
    modules_ = new std::vector<ModulePtr>[NUM_STAGES];
    payloadFactory_ = new PayloadFactory();
    payloads_ = new PayloadTypeMap();
  }

  Pipeline::~Pipeline()
  {
    delete[] modules_;
    delete payloadFactory_;
    delete payloads_;
  }

  bool Pipeline::execute()
  {
    
    for (int stage = 0; stage < NUM_STAGES; stage++)
    {
      for (int module = 0; module < modules_[stage].size(); module++)
      {
        modules_[stage][module]->processPayloads(*payloads_);
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

    // Register module's payloads with payload factory and
    // instantiate any newly generated payloads.
    for (auto type : newModule->registerTypes(*payloadFactory_))
    {
        (*payloads_)[type] = (*payloadFactory_).createPayload(type);
    }

    return true;
  }
}
