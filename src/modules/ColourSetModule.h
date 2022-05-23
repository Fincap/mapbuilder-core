#pragma once
#include "APIExport.h"

#include <vector>
#include <typeindex>
#include <map>

#include "core\Module.h"
#include "core\PipelineStage.h"
#include "payloads\ColourSetPayload.h"
#include "util\ModuleHelpers.h"

namespace mbc
{
  /*
  Module containing a set of height values (0-255) and a respective RGB colour.
  This module will generate a ColourSetPayload to be consumed by other Render
  modules..
  */
  class MAPBUILDER_API ColourSetModule : public Module
  {
  public:
    ColourSetModule();

    // Inherit from base class - must be implemented
    TypeIndexVector registerTypes(PayloadFactory&) override;
    bool processPayloads(const PayloadTypeMap&) override;

    bool operator==(Module::Ptr) override;
    bool operator!=(Module::Ptr) override;

    // Processing parameters
    std::map<unsigned char, uint32_t>* colourRanges;

  };
}


// Inline definitions for operator overloads
inline bool mbc::ColourSetModule::operator==(Module::Ptr other)
{
  auto castOther = std::dynamic_pointer_cast<ColourSetModule>(other);
  if (castOther)
  {
    return (*colourRanges == *(castOther->colourRanges));
  }  // Return false if other cannot be cast to this Module.

  return false;
}


inline bool mbc::ColourSetModule::operator!=(Module::Ptr other)
{
  return !(this->operator==(other));
}
