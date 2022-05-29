#pragma once

#include <chrono>
#include <vector>
#include <typeindex>
#include <memory>
#include <unordered_map>
#include <iostream>

#include <cereal\cereal.hpp>
#include <cereal\archives\xml.hpp>
#include <cereal\types\memory.hpp>

#include "MapBuilderCore\APIExport.h"
#include "MapBuilderCore\Module.h"
#include "MapBuilderCore\Payload.h"
#include "MapBuilderCore\PayloadFactory.h"
#include "MapBuilderCore\StageMap.h"

namespace mbc
{
  /*
  Pipeline is the core class of the library; it is responsible for the
  management, execution, and output of the modules provided by the implementor.
  */
  class MAPBUILDER_API Pipeline
  {
  public:
    Pipeline();
    ~Pipeline();

    /* Executes the Pipeline processing, calling all Modules in order and
    passing their payloads down the pipe.
    Returns true if there are no errors while executing the Pipeline. */
    bool execute();

    /* Adds a new shared_ptr to to the Pipeline's list of Modules, grouped by
    the appropriate PipelineStage. If a Module utilizes a payload that is not
    in the Pipeline's current list of Payloads, it will be registered to the
    list.
    Returns true if Module was successfully added to Pipeline. */
    bool addModule(Module::Ptr);

    /* Adds a shared_ptr to a Payload to the Pipeline's list of Payloads. This
    will overwrite any existing Payload of the given type, or provide a
    baseline Payload for module processing.*/
    void setPayload(Payload::Ptr);

    /* Returns a pointer to the Payload of the given type. */
    Payload::Ptr getPayload(std::type_index);

    /* Returns a reference to the Pipeline's map of Modules. */
    StageMap<Module::Ptr>& getModuleMap() const;

    /* Clears the Pipeline's list of Modules. */
    void clear();

    /* Serialize all modules currently loaded into the Pipeline. */
    template<typename Archive>
    void save(Archive& archive) const;

    /* Deserialize newly loaded modules into the Pipeline. */
    template<typename Archive>
    void load(Archive& archive);

  private:
    /* Array of vectors containing Modules in their respective stages. There is
    a vector for each Pipeline Stage, and each vector contains the Pipeline's
    modules in order of execution.*/
    StageMap<Module::Ptr>* modules_;

    /* The Pipeline's PayloadFactory, responsible for the instantiation of
    registered Payloads. */
    PayloadFactory* payloadFactory_;

    /* Unordered map of the Pipeline's registered payloads, where the key is
    the Payload's type_index and the value is the Payload instance. */
    PayloadTypeMap* payloads_;

  };
}


// Inline definitions
template<typename Archive>
inline void mbc::Pipeline::save(Archive& archive) const
{
  // Serialize modules
  archive(
    CEREAL_NVP(*modules_)
  );
}


template<typename Archive>
inline void mbc::Pipeline::load(Archive& archive)
{
  // Clear all existing data and delete the existing module map.
  clear();
  delete modules_;
  
  // Deserialize into buffer, then copy into new modules map. This is necessary
  // as cereal library cannot serialize raw pointers.
  StageMap<Module::Ptr> modulesBuffer;
  archive(
    modulesBuffer
  );

  modules_ = new StageMap<Module::Ptr>();

  // Rather than copy buffer StageMap directly into modules map, iterate
  // through every Module in the buffer and pass the module into the Pipeline's
  // addModule method as to ensure the correct registration and instantiation
  // of Payloads.
  for (auto& mod : modulesBuffer.getAll())
  {
    addModule(mod);
  }

}
