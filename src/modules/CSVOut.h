#pragma once
#include "APIExport.h"

#include <fstream>
#include <iostream>
#include <string>
#include <charconv>
#include <filesystem>

#include "core\Module.h"
#include "payloads\Heightmap.h"
#include "util\OutputValidation.h"
#include "util\ModuleHelpers.h"

namespace mbc
{
  /*
  Module that produces a CSV file at the given filepath where each value is the
  raw height (0-255) of its corresponding point on the heightmap.
  */
  class MAPBUILDER_API CSVOut : public Module
  {
  public:
    CSVOut();

    // Inherit from base class - must be implemented
    TypeIndexVector registerTypes(PayloadFactory&) override;
    bool processPayloads(const PayloadTypeMap&) override;

    bool operator==(Module::Ptr) override;
    bool operator!=(Module::Ptr) override;

    // Processing parameters
    char* outputFilepath;
  };
}


// Inline definitions for operator overloads
inline bool mbc::CSVOut::operator==(Module::Ptr other)
{
  auto castOther = std::dynamic_pointer_cast<CSVOut>(other);
  if (castOther)
  {
    return strcmp(this->outputFilepath, castOther->outputFilepath) == 0;
  }  // Return false if other cannot be cast to this Module.

  return false;
}


inline bool mbc::CSVOut::operator!=(Module::Ptr other)
{
  return !(this->operator==(other));
}
