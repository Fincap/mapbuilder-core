#pragma once
#include "APIExport.h"

#include <fstream>
#include <iostream>
#include <filesystem>

#include "core\Module.h"
#include "payloads\Heightmap.h"
#include "util\OutputValidation.h"
#include "util\ModuleHelpers.h"

namespace mbc
{
  /*
  Module that generates an 8-bit grayscale BMP file from the Heightmap payload
  and writes the BMP file to the given filepath parameter.
  */
  class MAPBUILDER_API BMP8Out : public Module
  {
  public:
    BMP8Out();

    // Inherit from base class - must be implemented
    TypeIndexVector registerTypes(PayloadFactory&) override;
    bool processPayloads(const PayloadTypeMap&) override;

    bool operator==(Module::Ptr) override;
    bool operator!=(Module::Ptr) override;

    // Processing parameters
    char* outputFilepath;

  private:
    /* This function splits the value parameter into 4 bytes, and then inserts
    the bytes into the given byte pointer. */
    void insertIntAsBytes(unsigned char*, int);
  };
}


// Inline definitions for operator overloads
inline bool mbc::BMP8Out::operator==(Module::Ptr other)
{
  auto castOther = std::dynamic_pointer_cast<BMP8Out>(other);
  if (castOther)
  {
    return strcmp(this->outputFilepath, castOther->outputFilepath) == 0;
  }  // Return false if other cannot be cast to this Module.

  return false;
}


inline bool mbc::BMP8Out::operator!=(Module::Ptr other)
{
  return !(this->operator==(other));
}
