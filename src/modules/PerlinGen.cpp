#include "PerlinGen.h"
namespace mbc
{
  PerlinGen::PerlinGen()
    : Module(PipelineStage::GENERATION),
    seed_(12345), frequency_(4.0), octaves_(6)
  { }

  std::vector<std::type_index> PerlinGen::getInputTypes()
  {
    return std::vector<std::type_index>
    {
      std::type_index(typeid(Heightmap))
    };
  }

  std::vector<std::type_index> PerlinGen::getOutputTypes()
  {
    return std::vector<std::type_index>
    {
      std::type_index(typeid(Heightmap))
    };
  }

  bool PerlinGen::processPayloads(PayloadTypeMap payloads)
  {

    // Get Heightmap payload
    PayloadPtr payloadPtr = payloads[std::type_index(typeid(Heightmap))];

    // Cast generic Payload pointer to Heightmap pointer
    std::shared_ptr<Heightmap> heightmapPtr = std::dynamic_pointer_cast<Heightmap>(payloadPtr);

    // Seed perlin noise
    siv::PerlinNoise perlin(seed_);

    // Calculate frequencies
    const double fx = heightmapPtr->width / frequency_;
    const double fy = heightmapPtr->height / frequency_;

    // Generate noise
    for (int y = 0; y < heightmapPtr->height; y++)
    {
      for (int x = 0; x < heightmapPtr->width; x++)
      {
        double noiseLevel = perlin.accumulatedOctaveNoise2D_0_1(x / fx, y / fy, octaves_);
        int index = (y * heightmapPtr->height) + x;
        heightmapPtr->points[index] *= noiseLevel;
      }
    }

    return true;
  }
}