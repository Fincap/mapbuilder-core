#include "MapBuilderCore\modules\PerlinGen.h"

namespace mbc
{
  PerlinGen::PerlinGen()
    : Module(PipelineStage::GENERATION, "perlin_gen"),
    seed(12345), frequency(4.0), octaves(6)
  { }


  PerlinGen::Ptr PerlinGen::clone() const
  {
    auto copy = std::make_shared<PerlinGen>();
    copy->seed = seed;
    copy->frequency = frequency;
    copy->octaves = octaves;
    return copy;
  }


  TypeIndexVector PerlinGen::registerTypes(PayloadFactory& factory)
  {
    return registerWithFactory<Heightmap>(factory);
  }

  bool PerlinGen::processPayloads(const PayloadTypeMap& payloads)
  {

    // Get Heightmap payload
    auto heightmapPtr = util::getPtrToPayload<Heightmap>(payloads);

    int width = heightmapPtr->width;
    int height = heightmapPtr->height;

    // Calculate frequencies
    const double fx = width / frequency;
    const double fy = height / frequency;

#ifdef MBC_MULTI
    // Get boundaries of array
    auto begin = &heightmapPtr->points[0];
    auto size = width * height;

    // Arbitrary cutoff
    if (size <= 1024)
    {
      computePerlinGrid(begin, begin + size, fx, fy, octaves, 0, width, seed);
      return true;
    }

    auto q1 = size / 4;
    auto q2 = size / 2;
    auto q3 = size * 3/4;

    // Divide grid into 4 and make async calls to compute perlin grid.
    auto f0 = std::async(computePerlinGrid,
      begin, begin + q1, fx, fy, octaves, 0, width, seed);

    auto f1 = std::async(computePerlinGrid,
      begin + q1, begin + q2, fx, fy, octaves, q1, width, seed);

    auto f2 = std::async(computePerlinGrid,
      begin + q2, begin + q3, fx, fy, octaves, q2, width, seed);

    auto f3 = std::async(computePerlinGrid,
      begin + q3, begin + size, fx, fy, octaves, q3, width, seed);

    f0.wait();
    f1.wait();
    f2.wait();
    f3.wait();

#else

    siv::PerlinNoise perlin(seed);

    for (int y = 0; y < height; y++)
    {
      for (int x = 0; x < width; x++)
      {
        double noiseLevel = perlin.accumulatedOctaveNoise2D_0_1(x / fx, y / fy, octaves);
        heightmapPtr->points[(y * width) + x] *= noiseLevel;
      }
    }

#endif // MBC_MULTI

    return true;
  }


  void mbc::computePerlinGrid(unsigned char* begin, unsigned char* end, 
    const double& fx, const double& fy, const uint32_t& oct, 
    const int& startIndex, const int&  width, const uint32_t& seed)
  {
    // Seed perlin noise
    siv::PerlinNoise perlin(seed);

    int iters = 0;
    while (begin != end)
    {
      // Calculate index, x, and y
      int index = startIndex + iters;
      int x = index % width;
      int y = index / width;

      // Generate noise
      double noiseLevel = perlin.accumulatedOctaveNoise2D_0_1(x / fx, y / fy, oct);
      *begin = static_cast<unsigned char>(*begin * noiseLevel);

      iters++;
      begin++;
    }
  }
}
