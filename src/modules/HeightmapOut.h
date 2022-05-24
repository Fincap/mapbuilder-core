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
  Module that writes the Heightmap to a proprietary binary file format (.hmp),
  where the first 64 bits are the map's width (32 bit) and height (32 bit), and
  the remainder of the file is each height value (1 height value per byte).
  */
  class MAPBUILDER_API HeightmapOut : public Module
  {
  public:
    HeightmapOut();

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
inline bool mbc::HeightmapOut::operator==(Module::Ptr other)
{
  auto castOther = std::dynamic_pointer_cast<HeightmapOut>(other);
  if (castOther)
  {
    return strcmp(this->outputFilepath, castOther->outputFilepath) == 0;
  }  // Return false if other cannot be cast to this Module.

  return false;
}


inline bool mbc::HeightmapOut::operator!=(Module::Ptr other)
{
  return !(this->operator==(other));
}


template<typename Archive>
inline void mbc::HeightmapOut::save(Archive& archive) const
{
  // Serialize as string
  archive(
    CEREAL_NVP(std::string(outputFilepath))
  );
}


template<typename Archive>
inline void mbc::HeightmapOut::load(Archive& archive)
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


CEREAL_REGISTER_TYPE(mbc::HeightmapOut);
CEREAL_REGISTER_POLYMORPHIC_RELATION(mbc::Module, mbc::HeightmapOut);
