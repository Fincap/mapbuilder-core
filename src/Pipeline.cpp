#include "MapBuilderCore\Pipeline.h"

namespace mbc
{
  Pipeline::Pipeline()
  {
    modules_ = new StageMap<Module::Ptr>();
    payloadFactory_ = new PayloadFactory();
    payloads_ = new PayloadTypeMap();
  }


  Pipeline::~Pipeline()
  {
    delete modules_;
    delete payloadFactory_;
    delete payloads_;
  }


  bool Pipeline::execute(bool suppress)
  {
    // Log total execution time
    using namespace std::chrono;
    long long totalElapsed = 0;

    for (auto& mod : modules_->getAll())
    {
      // Log the time for each payload to process
      // Get time before
      auto timeBefore = high_resolution_clock::now();

      mod->processPayloads(*payloads_);

      // Output time after
      auto timeAfter = high_resolution_clock::now();
      auto timeDiff = duration_cast<milliseconds>(timeAfter - timeBefore).count();
      totalElapsed += timeDiff;

      if (!suppress)
      {
        std::clog << "MODULE " << mod->getModuleName() << " processing time: ";
        std::clog << timeDiff;
        std::clog << "ms" << std::endl;
      }
    }

    if (!suppress)
      std::cout << "Total execution time: " << totalElapsed << "ms" << std::endl;

    return true;
  }


  bool mbc::Pipeline::executeStage(mbc::PipelineStage stage)
  {
    return executeStage((int) stage);
  }


  bool mbc::Pipeline::executeStage(int stage)
  {
    for (auto& mod : modules_->getAll(stage))
    {
      mod->processPayloads(*payloads_);
    }

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
    if (newModuleStage < 0 || newModuleStage >= MBC_NUM_STAGES)
    {
      std::cerr << "Invalid PipelineStage for " << std::type_index(typeid(newModule)).name() << std::endl;
      return false;
    }
    else
    {
      modules_->add(newModule, newModuleStage);
    }

    // Register module's payloads with payload factory and
    // instantiate any newly generated payloads.
    for (auto& type : newModule->registerTypes(*payloadFactory_))
    {
        (*payloads_)[type] = (*payloadFactory_).createPayload(type);
    }

    return true;
  }


  StageMap<Module::Ptr>& mbc::Pipeline::getModuleMap() const
  {
    return *modules_;
  }


  void mbc::Pipeline::clear()
  {
    modules_->clear();
    payloads_->clear();
    payloadFactory_->clear();
  }
}
