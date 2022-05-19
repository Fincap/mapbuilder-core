#include "Pipeline.h"

namespace mbc
{
  Pipeline::Pipeline()
  {
    modules_ = new std::vector<Module::Ptr>[NUM_STAGES];
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
    // Log total execution time
    using namespace std::chrono;
    long long totalElapsed = 0;
    
    for (int stage = 0; stage < NUM_STAGES; stage++)
    {
      for (int module = 0; module < modules_[stage].size(); module++)
      {
        // Log the time for each payload to process
        // Get time before
        auto timeBefore = high_resolution_clock::now();

        modules_[stage][module]->processPayloads(*payloads_);

        // Output time after
        auto timeAfter = high_resolution_clock::now();
        auto& currentModule = modules_[stage][module];
        auto timeDiff = duration_cast<milliseconds>(timeAfter - timeBefore).count();
        totalElapsed += timeDiff;

        std::clog << "MODULE " << currentModule->getModuleName() << " processing time: ";
        std::clog << timeDiff;
        std::clog << "ms" << std::endl;

      }
    }

    std::clog << "Total execution time: " << totalElapsed << "ms" << std::endl;

    return true;
  }


  bool Pipeline::addModule(Module::Ptr newModule)
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


  void mbc::Pipeline::clear()
  {
    // Clear modules list.
    for (int i = 0; i < NUM_STAGES; i++)
    {
      modules_[i].clear();
    }

    // Clear payloads list.
    payloads_->clear();
  }
}
