#pragma once
#include "APIExport.h"

#include "core\Module.h"
#include "payloads\Heightmap.h"
#include "util\ModuleHelpers.h"

namespace mbc
{
  /*
  Module that applies a slope to the generated Heightmap by raising each value
  in the Heightmap to the power of the given elevation slope factor.
  */
  class MAPBUILDER_API ElevationSlope : public Module
  {
  public:
    ElevationSlope();

    // Inherit from base class - must be implemented
    TypeIndexVector registerTypes(PayloadFactory&) override;
    bool processPayloads(const PayloadTypeMap&) override;

    bool operator==(Module::Ptr) override;
    bool operator!=(Module::Ptr) override;

    // Processing parameters
    double slope;

    // Serialize module
    template<typename Archive>
    void serialize(Archive& archive);
  };
}

// Inline definitions for operator overloads
inline bool mbc::ElevationSlope::operator==(Module::Ptr other)
{
  auto castOther = std::dynamic_pointer_cast<ElevationSlope>(other);
  if (castOther)
  {
    return (slope == castOther->slope);
  }  // Return false if other cannot be cast to this Module.

  return false;
}


inline bool mbc::ElevationSlope::operator!=(Module::Ptr other)
{
  return !(this->operator==(other));
}


template<typename Archive>
inline void mbc::ElevationSlope::serialize(Archive& archive)
{
  archive(
    CEREAL_NVP(slope)
  );
}


CEREAL_REGISTER_TYPE(mbc::ElevationSlope);
CEREAL_REGISTER_POLYMORPHIC_RELATION(mbc::Module, mbc::ElevationSlope);
