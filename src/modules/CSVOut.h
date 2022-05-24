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

    // Serialize module - split functions
    template<typename Archive>
    void save(Archive& archive) const;

    template<typename Archive>
    void load(Archive& archive);
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


template<typename Archive>
inline void mbc::CSVOut::save(Archive& archive) const
{
  // Serialize as string
  archive(
    CEREAL_NVP(std::string(outputFilepath))
  );
}


template<typename Archive>
inline void mbc::CSVOut::load(Archive& archive)
{
  // Deserialize into string buffer, then copy into outputFilepath. This is
  // necessary as cereal library cannot serialize raw pointers.
  std::string filepathBuffer;
  archive(
    filepathBuffer
  );

  outputFilepath = new char[MBC_MAX_PATH];
  std::copy(filepathBuffer.begin(), filepathBuffer.end(), outputFilepath);
  outputFilepath[filepathBuffer.size()] = '\0'; // Null terminate new filepath.
}
