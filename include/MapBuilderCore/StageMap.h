#pragma once

#include <vector>
#include <stdexcept>

#include <cereal\types\array.hpp>
#include <cereal\types\vector.hpp>
#include <cereal\types\string.hpp>

#include "MapBuilderCore\APIExport.h"
#include "MapBuilderCore\Module.h"
#include "MapBuilderCore\PipelineStage.h"
#include "MapBuilderCore\util\ModuleHelpers.h"

namespace mbc
{
  /*
  This templated class acts as a handle for a map of PipelineStages and a list of
  respective values. It is used to provide convenience for storing, iterating,
  and updating a list of objects based on their Pipeline stage.
  */
  template <typename T>
  class StageMap
  {
  public:
    // Iterator types
    using iterator = T*;
    using const_iterator = T const*;

    StageMap();
    ~StageMap();
    StageMap(const StageMap&);        // Copy constructor


    void add(T, mbc::PipelineStage);  // Add T to given stage.
    void add(T, int);                 // Add T to given stage.
    void clear();                     // Clear all values.

    std::vector<T>& getAll(mbc::PipelineStage);  // Get all in given stage.
    std::vector<T>& getAll(int);                 // Get all in given stage.
    std::vector<T> getAll();                     // Get all in all stages.

    // Iterator functions
    iterator begin() { return &map_[0]; }
    iterator end() { return &map_[MBC_NUM_STAGES]; }
    const_iterator begin() const { return &map_[0]; }
    const_iterator end() const { return &map_[MBC_NUM_STAGES]; }

    /* Serialize each T existing within the map. */
    template<typename Archive>
    void save(Archive& archive) const;

    /* Serialize newly loaded T into the map. */
    template<typename Archive>
    void load(Archive& archive);

  private:
    std::vector<T>* map_;

  };


  template<typename T>
  inline StageMap<T>::StageMap()
  {
    map_ = new std::vector<T>[MBC_NUM_STAGES];
  }


  template<typename T>
  inline StageMap<T>::~StageMap()
  {
    delete[] map_;
  }


  template<typename T>
  inline StageMap<T>::StageMap(const StageMap& other)
  {
    map_ = new std::vector<T>[MBC_NUM_STAGES];
    for (int stage = 0; stage < MBC_NUM_STAGES; stage++)
    {
      map_[stage] = other.map_[stage];
    }
  }


  template<typename T>
  inline void StageMap<T>::add(T value, mbc::PipelineStage stage)
  {
    add(value, (int)stage);
  }


  template<typename T>
  inline void StageMap<T>::add(T value, int stage)
  {
    if (stage >= MBC_NUM_STAGES)
      throw std::out_of_range{ "PipelineStage out of range." };

    map_[stage].push_back(value);
  }


  template<typename T>
  inline void StageMap<T>::clear()
  {
    for (int stage = 0; stage < MBC_NUM_STAGES; stage++)
    {
      map_[stage].clear();
    }
  }


  template<typename T>
  inline std::vector<T>& StageMap<T>::getAll(mbc::PipelineStage stage)
  {
    return getAll((int)stage);
  }


  template<typename T>
  inline std::vector<T>& StageMap<T>::getAll(int stage)
  {
    if (stage >= MBC_NUM_STAGES)
      throw std::out_of_range{ "PipelineStage out of range." };
    return map_[stage];
  }


  template<typename T>
  inline std::vector<T> StageMap<T>::getAll()
  {
    std::vector<T> all;

    for (int stage = 0; stage < MBC_NUM_STAGES; stage++)
    {
      for (auto& val : map_[stage])
        all.push_back(val);
    }

    return all;
  }


  template<typename T>
  template<typename Archive>
  inline void StageMap<T>::save(Archive& archive) const
  {
    // Copy T vectors into STL array, then serialize the STL array.
    std::array<std::vector<T>, MBC_NUM_STAGES> buffer;
    for (int stage = 0; stage < MBC_NUM_STAGES; stage++)
    {
      buffer[stage] = map_[stage];
    }

    archive(
      buffer
    );
  }


  template<typename T>
  template<typename Archive>
  inline void StageMap<T>::load(Archive& archive)
  {
    // Deserialize the STL array into a raw pointer array.
    delete[] map_;
    std::array<std::vector<T>, MBC_NUM_STAGES> buffer;

    archive(
      buffer
    );

    map_ = new std::vector<T>[MBC_NUM_STAGES];
    for (int stage = 0; stage < MBC_NUM_STAGES; stage++)
    {
      map_[stage] = buffer[stage];
    }
  }

}