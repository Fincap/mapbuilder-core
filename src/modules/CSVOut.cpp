#include "CSVOut.h"

namespace mbc
{
  CSVOut::CSVOut()
    : Module(PipelineStage::OUTPUT, "csv_out")
  {
    outputFilepath = new char[256]{ "out/heightmap.csv" };
  }

  std::vector<std::type_index> CSVOut::registerTypes(PayloadFactory& factory)
  {
    return registerWithFactory<Heightmap>(factory);
  }

  bool CSVOut::processPayloads(const PayloadTypeMap& payloads)
  {

    // Get Heightmap payload
    auto heightmapPtr = util::getPtrToPayload<Heightmap>(payloads);

    std::cout << "Writing heightmap to file: " << outputFilepath << std::endl;

    // Get width and height from heightmap
    int width = heightmapPtr->width;
    int height = heightmapPtr->height;

    // Create output string to be placed in fstream
    std::string output;

    // Create buffer to store height value as char
    char* ptBuffer = new char[4];  // ['x', 'x', 'x', '\0']

    // Insert each value to string buffer
    for (int y = 0; y < height; y++)
    {
      for (int x = 0; x < width; x++)
      {
        // (x, y) to 1D index formula: (y * height) + x
        uint8_t point = heightmapPtr->points[(y * height) + x];
        memset(ptBuffer, '\0', 4); // Nil out buffer
        std::to_chars(ptBuffer, ptBuffer + 3, point); // Point to cstring
        output += ptBuffer;  // Append point cstring to output string
        if (x < width - 1)
          output += ',';
      }
      output += '\n';
    }

    // Output filepath validation.
    std::filesystem::path path{ outputFilepath };
    util::validateOutputFilepath(path, "heightmap.csv");

    // Open output file stream
    std::ofstream outfile;
    outfile.open(path, std::ios::trunc | std::ios::binary);

    if (outfile.fail())
    {
      std::cerr << "Failed to open output file" << std::endl;
      return false;
    }

    // Write buffer to file
    outfile.write(output.c_str(), output.size());

    // Close file
    outfile.close();
    std::cout << "CSV output completed" << std::endl;

    return true;
  }

}