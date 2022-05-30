#include "MapBuilderCore\modules\HeightmapOut.h"

namespace mbc
{
  HeightmapOut::HeightmapOut()
    : Module(PipelineStage::OUTPUT, "heightmap_out")
  {
    outputFilepath = new char[MBC_MAX_PATH]{ "out/outmap.hmp" };
  }


  HeightmapOut::~HeightmapOut()
  {
    delete[] outputFilepath;
  }


  HeightmapOut::Ptr HeightmapOut::clone() const
  {
    auto copy = std::make_shared<HeightmapOut>();
    memset(copy->outputFilepath, 0, MBC_MAX_PATH);
    std::copy(outputFilepath, outputFilepath + MBC_MAX_PATH, copy->outputFilepath);
    return copy;
  }


  TypeIndexVector HeightmapOut::registerTypes(PayloadFactory& factory)
  {
    return registerWithFactory<Heightmap>(factory);
  }

  bool HeightmapOut::processPayloads(const PayloadTypeMap& payloads)
  {

    // Get Heightmap payload
    auto heightmapPtr = util::getPtrToPayload<Heightmap>(payloads);

    std::clog << "Writing heightmap to file: " << outputFilepath << std::endl;

    // Output filepath validation.
    std::filesystem::path path{ outputFilepath };
    util::validateOutputFilepath(path, "heightmap.hmp");

    // Output heightmap to file
    std::ofstream outfile;
    outfile.open(path, std::ios::trunc | std::ios::binary);

    if (outfile.fail())
    {
      std::cerr << "Failed to open output file" << std::endl;
      return false;
    }

    // First 64 bits are width (32 bit) and height (32 bit)
    int32_t width = heightmapPtr->width;
    int32_t height = heightmapPtr->height;

    // Write width and height to file
    outfile.write(reinterpret_cast<const char*>(&width), sizeof(width));
    outfile.write(reinterpret_cast<const char*>(&height), sizeof(height));

    // Calculate points array size
    int32_t heightmapSize = width * height;

    // Remainder of file contains 1 byte per height value
    for (int32_t i = 0; i < heightmapSize; i++) {
      uint8_t value = heightmapPtr->points[i];
      outfile.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }

    outfile.close();

    std::clog << heightmapSize + 8 << " bytes written" << std::endl;

    return true;
  }

}