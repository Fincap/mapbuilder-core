#include "CSVOut.h"

namespace mbc
{
  CSVOut::CSVOut()
    : Module(PipelineStage::OUTPUT, "csv_out"),
    outputFilepath("../out/heightmap.csv")
  { }

  std::vector<std::type_index> CSVOut::registerTypes(PayloadFactory& factory)
  {
    return registerWithFactory<Heightmap>(factory);
  }

  bool CSVOut::processPayloads(PayloadTypeMap payloads)
  {

    // Get Heightmap payload
    PayloadPtr payloadPtr = payloads[std::type_index(typeid(Heightmap))];

    // Cast generic Payload pointer to Heightmap pointer
    std::shared_ptr<Heightmap> heightmapPtr = std::dynamic_pointer_cast<Heightmap>(payloadPtr);

    std::cout << "Writing heightmap to file: " << outputFilepath << std::endl;

    // Output heightmap to file
    std::ofstream outfile;
    outfile.open(outputFilepath, std::ios::trunc | std::ios::binary);

    if (outfile.fail())
    {
      std::cerr << "Failed to open output file" << std::endl;
      return false;
    }

    // Get width and height from heightmap
    int width = heightmapPtr->width;
    int height = heightmapPtr->height;

    // Output each line to csv
    for (int y = 0; y < height; y++)
    {
      for (int x = 0; x < width; x++)
      {
        //(y * height) + x
        outfile << +heightmapPtr->points[(y * height) + x];
        if (x < width - 1)
          outfile << ",";
      }
      outfile << std::endl;
    }

    outfile.close();

    std::cout << "CSV output completed" << std::endl;

    return true;
  }

}