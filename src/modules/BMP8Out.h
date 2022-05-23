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

    // Processing parameters
    char* outputFilepath;

  private:
    /* This function splits the value parameter into 4 bytes, and then inserts
    the bytes into the given byte pointer. */
    void insertIntAsBytes(unsigned char*, int);
  };
}