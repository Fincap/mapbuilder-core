#pragma once
#include "APIExport.h"

#ifdef _DEBUG
#include <chrono>
#endif

#include <vector>
#include <typeindex>
#include <memory>
#include <unordered_map>
#include <iostream>

#include "Module.h"
#include "Payload.h"
#include "PayloadFactory.h"

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



  private:
    /* Array of vectors containing Modules in their respective stages. There is
    a vector for each Pipeline Stage, and each vector contains the Pipeline's
    modules in order of execution.*/
    std::vector<Module::Ptr>* modules_;

    /* The Pipeline's PayloadFactory, responsible for the instantiation of
    registered Payloads. */
    PayloadFactory* payloadFactory_;

    /* Unordered map of the Pipeline's registered payloads, where the key is
    the Payload's type_index and the value is the Payload instance. */
    PayloadTypeMap* payloads_;

  };
}
