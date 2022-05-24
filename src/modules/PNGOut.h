#pragma once
#include "APIExport.h"

#include <iostream>
#include <filesystem>

#include <png++\png.hpp>

#include "core\Module.h"
#include "payloads\ColouredHeightmap.h"
#include "util\OutputValidation.h"
#include "util\ModuleHelpers.h"

namespace mbc
{
  /*
  Module that writes the ColouredHeightmap payload to a PNG file at the given
  filepath.
  */
  class MAPBUILDER_API PNGOut : public Module
  {
  public:
    PNGOut();

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
inline bool mbc::PNGOut::operator==(Module::Ptr other)
{
  auto castOther = std::dynamic_pointer_cast<PNGOut>(other);
  if (castOther)
  {
    return strcmp(this->outputFilepath, castOther->outputFilepath) == 0;
  }  // Return false if other cannot be cast to this Module.

  return false;
}


inline bool mbc::PNGOut::operator!=(Module::Ptr other)
{
  return !(this->operator==(other));
}


template<typename Archive>
inline void mbc::PNGOut::save(Archive& archive) const
{
  // Serialize as string
  archive(
    CEREAL_NVP(std::string(outputFilepath))
  );
}


template<typename Archive>
inline void mbc::PNGOut::load(Archive& archive)
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
