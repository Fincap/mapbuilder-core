#pragma once

#include <vector>
#include <typeindex>
#include <memory>

#include <cereal\cereal.hpp>
#include <cereal\archives\xml.hpp>
#include <cereal\types\memory.hpp>
#include <cereal\types\base_class.hpp>
#include <cereal\types\polymorphic.hpp>

#include "MapBuilderCore\APIExport.h"
#include "MapBuilderCore\PipelineStage.h"
#include "MapBuilderCore\Payload.h"
#include "MapBuilderCore\PayloadFactory.h"

namespace mbc
{
  // Convenience typing - pre-class declaration
  using TypeIndexVector = std::vector<std::type_index>;

  /*
  Abstract base class that defines a class that modifies the Pipeline's
  Payloads. The derived classes will define a series of processing parameters
  that will modify a set of Payloads. The Modules are responsible for declaring
  which Payload types it will consume and produce, and will register those
  types with the PayloadFactory.
  */
  class MAPBUILDER_API Module
  {
  public:
    /* Convenience typing - shared_ptr to Module. */
    using Ptr = std::shared_ptr<Module>;

    /* Derived class constructors will call Module's constructor to instantiate
    derived Module's stage and unique name. */
    Module(PipelineStage, const char*);

    /* Copy constructor to be implemented by derived classes. */
    virtual Module::Ptr clone() const = 0;

    /* This method registers all types with the linked factory, and returns a list of
    any types that were newly registered so they can be instantiated. */
    virtual TypeIndexVector registerTypes(PayloadFactory&) = 0;

    /* Executes the Module's processing on the given map of Payloads. */
    virtual bool processPayloads(const PayloadTypeMap&) = 0;
    
    virtual PipelineStage getPipelineStage() final;
    virtual const char* getModuleName() final;

    /* Overloaded equality operators - must be implemented by derived classes.
    Usage: Module == Module::Ptr (necessary as to allow comparison between
    Modules of unknown type. */
    virtual bool operator==(Module::Ptr) = 0;
    virtual bool operator!=(Module::Ptr) = 0;

  protected:
    const PipelineStage PIPELINE_STAGE;
    const char* MODULE_NAME;

    /* This method will be called by derived classes to simplify the type
     registration process for the implementer. */
    template <typename... Ts>
    TypeIndexVector registerWithFactory(PayloadFactory&);

  private:
    /* Consumer of registerWithFactory variadic template */
    template <typename T>
    void registerSingle(PayloadFactory&, TypeIndexVector&);

    /* Allow serialization of non - public members. */
    friend class cereal::access;

  };


  // Inline definition of default constructor - to be called by derived class
  inline Module::Module(PipelineStage stage, const char* name) :
    PIPELINE_STAGE(stage),
    MODULE_NAME(name)
  {}


  // Inline definition to preserve runtime mutability of PipelineStage
  inline PipelineStage Module::getPipelineStage()
  {
    return PIPELINE_STAGE;
  }


  // Inline definition to preserve runtime mutability of module name
  inline const char* Module::getModuleName()
  {
    return MODULE_NAME;
  }


  // Inline definition of internalRegisterType
  template <typename... Ts>
  inline TypeIndexVector Module::registerWithFactory(PayloadFactory& factory)
  {
    TypeIndexVector newPayloads;

    (registerSingle<Ts>(factory, newPayloads), ...);

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

}
