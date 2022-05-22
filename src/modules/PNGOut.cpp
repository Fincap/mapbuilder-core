#include "PNGOut.h"

namespace mbc
{
  PNGOut::PNGOut()
    : Module(PipelineStage::OUTPUT, "png_out")
  {
    outputFilepath = new char[256]{ "out/heightmap.png" };
  }

  TypeIndexVector PNGOut::registerTypes(PayloadFactory& factory)
  {
    return registerWithFactory<ColouredHeightmap>(factory);
  }

  bool PNGOut::processPayloads(const PayloadTypeMap& payloads)
  {
    // Get coloured heightmap pointer
    auto heightmapPtr = util::getPtrToPayload<ColouredHeightmap>(payloads);

    std::cout << "Writing PNG to file: " << outputFilepath << std::endl;

    // Get width and height
    int width = heightmapPtr->width;
    int height = heightmapPtr->height;

    // Create PNG image
    png::image<png::rgba_pixel> image(width, height);

    // Insert each colouredPoint to PNG image
    for (int y = 0; y < height; y++)
    {
      for (int x = 0; x < width; x++)
      {
        // Get RGB from colouredPoint
        auto colour = heightmapPtr->colouredPoints[(y * height) + x];
        unsigned char b = colour & 0xff;
        unsigned char g = (colour >> 8) & 0xff;
        unsigned char r = (colour >> 16) & 0xff;

        // Add to PNG image
        image[y][x] = png::rgba_pixel(r, g, b);
      }
    }

    // Output filepath validation.
    std::filesystem::path path{ outputFilepath };
    util::validateOutputFilepath(path, "render.png");

    // Finally write PNG output to file.
    image.write(path.string());

    std::cout << "PNG write complete" << std::endl;

    return true;
  }

}