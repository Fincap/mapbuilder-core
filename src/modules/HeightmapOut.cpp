#include "HeightmapOut.h"

namespace mbc
{
  HeightmapOut::HeightmapOut()
    : Module(PipelineStage::OUTPUT),
    outputFilepath_("../out/heightmap.hmp")
  { }

  std::vector<std::type_index> HeightmapOut::registerTypes(PayloadFactory& factory)
  {
    return registerWithFactory<Heightmap>(factory);
  }

  bool HeightmapOut::processPayloads(PayloadTypeMap payloads)
  {

    // Get Heightmap payload
    PayloadPtr payloadPtr = payloads[std::type_index(typeid(Heightmap))];

    // Cast generic Payload pointer to Heightmap pointer
    std::shared_ptr<Heightmap> heightmapPtr = std::dynamic_pointer_cast<Heightmap>(payloadPtr);

    std::cout << "Writing heightmap to file: " << outputFilepath_ << std::endl;

    // Output heightmap to file
    std::ofstream outfile;
    outfile.open(outputFilepath_, std::ios::trunc | std::ios::binary);

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

    std::cout << heightmapSize + 8 << " bytes written" << std::endl;

    return true;
  }

}