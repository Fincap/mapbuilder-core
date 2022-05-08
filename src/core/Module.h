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
  // Convenience typing - pre-class declaration
  using TypeIndexVector = std::vector<std::type_index>;

  class MAPBUILDER_API Module
  {
  public:
    Module(PipelineStage);

    // This method registers all types with the linked factory, and returns a list of
    // any types that were newly registered so they can be instantiated.
    virtual TypeIndexVector registerTypes(PayloadFactory&) = 0;

    virtual bool processPayloads(PayloadTypeMap) = 0;

    virtual PipelineStage getPipelineStage() final;

  protected:
    const PipelineStage PIPELINE_STAGE;

    // This method will be called by derived classes to simplify the type
    // registration process for the implementer.
    template <typename... Ts>
    TypeIndexVector registerWithFactory(PayloadFactory&);

  private:
    // Consumer of registerWithFactory variadic template
    template <typename T>
    void registerSingle(PayloadFactory&, TypeIndexVector&);

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

  // Inline definition of internalRegisterType
  template <typename... Ts>
  inline TypeIndexVector Module::registerWithFactory(PayloadFactory& factory)
  {
    TypeIndexVector newPayloads;

    registerSingle<Ts...>(factory, newPayloads);

    return newPayloads;
  }

  template <typename T>
  inline void Module::registerSingle(PayloadFactory& factory, TypeIndexVector& typeList)
  {
    if (!factory.hasPayload<T>())
    {
      factory.registerPayload<T>();
      typeList.push_back(std::type_index(typeid(T)));
    }
  }

  // Convenience typing - post-class declaration
  using ModulePtr = std::shared_ptr<Module>;

}