#pragma once

#include <vector>
#include <typeindex>
#include <map>
#include <cereal\types\map.hpp>

#include "MapBuilderCore\APIExport.h"
#include "MapBuilderCore\Module.h"
#include "MapBuilderCore\PipelineStage.h"
#include "MapBuilderCore\util\ModuleHelpers.h"
#include "MapBuilderCore\payloads\Heightmap.h"
#include "MapBuilderCore\payloads\ColouredHeightmap.h"

namespace mbc
{
  /*
  Module containing a set of height values (0-255) and a respective RGB colour.
  This module will generate a new coloured heightmap payload based on the
  selected colour ranges.
  */
  class MAPBUILDER_API ColourSetModule : public Module
  {
  public:
    ColourSetModule();
    ~ColourSetModule();
    ColourSetModule::Ptr clone() const override;

    // Inherit from base class - must be implemented
    TypeIndexVector registerTypes(PayloadFactory&) override;
    bool processPayloads(const PayloadTypeMap&) override;

    bool operator==(Module::Ptr) override;
    bool operator!=(Module::Ptr) override;

    // Processing parameter
    /* A set of ranges (0-50, 51-70, 71-100, etc)
    Each range has a corresponding RGB.
    Key stores the max value in the range.
    Value stores the RBG colour 0xRRGGBB. */
    std::map<unsigned char, uint32_t>* colourRanges;

    // Serialize module - split functions
    template<typename Archive>
    void save(Archive& archive) const;

    template<typename Archive>
    void load(Archive& archive);

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


template<typename Archive>
inline void mbc::ColourSetModule::save(Archive& archive) const
{
  // Serialize pointed-to map.
  archive(
    CEREAL_NVP(*colourRanges)
  );
}


template<typename Archive>
inline void mbc::ColourSetModule::load(Archive& archive)
{
  // Deserialize into buffer, then copy into pointer to new colour ranges. This
  // is necessary as cereal library cannot serialize raw pointers.
  std::map<unsigned char, uint32_t> rangesBuffer;
  archive(
    rangesBuffer
  );

  colourRanges = new std::map<unsigned char, uint32_t>(rangesBuffer);
}


CEREAL_REGISTER_TYPE(mbc::ColourSetModule);
CEREAL_REGISTER_POLYMORPHIC_RELATION(mbc::Module, mbc::ColourSetModule);
