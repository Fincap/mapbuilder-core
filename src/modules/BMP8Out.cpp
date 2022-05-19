#include "BMP8Out.h"

namespace mbc
{
  BMP8Out::BMP8Out()
    : Module(PipelineStage::OUTPUT, "bmp8_out"),
    outputFilepath("out/heightmap.bmp")
  { }

  std::vector<std::type_index> BMP8Out::registerTypes(PayloadFactory& factory)
  {
    return registerWithFactory<Heightmap>(factory);
  }

  bool BMP8Out::processPayloads(PayloadTypeMap payloads)
  {
    // Get Heightmap payload
    Payload::Ptr payloadPtr = payloads[std::type_index(typeid(Heightmap))];

    // Cast generic Payload pointer to Heightmap pointer
    auto heightmapPtr = std::dynamic_pointer_cast<Heightmap>(payloadPtr);

    std::cout << "Writing heightmap to file: " << outputFilepath << std::endl;

    // Convert heightmap properties into total BMP filesize
    int width = heightmapPtr->width;
    int height = heightmapPtr->height;
    int filesize = 1078 + width * height; // 1078 is BMP header size (54) + color table size (1024)

    // Initialise pixel array
    size_t s_width = width;
    size_t s_height = height;
    unsigned char* img = new unsigned char[s_width * s_height];
    memset(img, 0, (s_width * s_height));

    // Populate pixel array
    for (int i = 0; i < width; i++)
    {
      for (int j = 0; j < height; j++)
      {
        auto x = i;
        auto y = (height - 1) - j;
        img[x + y * width] = heightmapPtr->points[x + y * width];
      }
    }

    // Create BMP file header
    unsigned char bmpFileHeader[14] =
    {
      'B', 'M',     // 00: BMP magic number
      0, 0, 0, 0,   // 02: Size of BMP file in bytes
      0, 0, 0, 0,   // 06, 08: Reserved (always 0)
      0, 0, 0, 0,   // 0A: Pixel array offset (after headers)
    };

    // Set header file size (02) and pixel array offset (0A)
    insertIntAsBytes(bmpFileHeader + 2, filesize);
    insertIntAsBytes(bmpFileHeader + 10, 1024);

    // Create BMP info header
    unsigned char bmpInfoHeader[40] =
    {
      40, 0, 0, 0,  // 0E: Size of header in bytes (BITMAPINFOHEADER)
      0, 0, 0, 0,   // 12: BMP width in pixels
      0, 0, 0, 0,   // 16: BMP height in pixels
      1, 0,         // 1A: Number of colour planes (must be 1)
      8, 0,         // 1C: Number of bits per pixel
    };  // Remaining fields all set to 0

    // Set header info width (12) and height (16)
    insertIntAsBytes(bmpInfoHeader + 4, width);
    insertIntAsBytes(bmpInfoHeader + 8, height);

    // Create BMP colour table (necessary where bits per pixel <= 8)
    // 1024 = 256 * 4: 256 color table entries with 4 bytes each
    unsigned char bmpColorTable[1024] = { 0 };
    for (int i = 0; i < 256; i++)
    {
      bmpColorTable[i * 4 + 0] = (unsigned char)i;  // B
      bmpColorTable[i * 4 + 1] = (unsigned char)i;  // G
      bmpColorTable[i * 4 + 2] = (unsigned char)i;  // R
    }  // Remaining byte is reserved and remains as 0

    // Output filepath validation.
    std::filesystem::path path{ outputFilepath };
    util::validateOutputFilepath(path, "heightmap.bmp");

    // Open output file
    std::ofstream outfile;
    outfile.open(path, std::ios::trunc | std::ios::binary);

    if (outfile.fail())
    {
      std::cerr << "Failed to open output file" << std::endl;
      return false;
    }

    // Write headers and color table to file
    outfile.write(reinterpret_cast<const char*>(bmpFileHeader), 14);
    outfile.write(reinterpret_cast<const char*>(bmpInfoHeader), 40);
    outfile.write(reinterpret_cast<const char*>(bmpColorTable), 1024);

    // Padding source string - necessary as ofstream.write requires const char*
    unsigned char padding[3] = { 0, 0, 0 };

    // Write pixels to file
    for (int i = 0; i < height; i++)
    {
      // Write row-by-row
      outfile.write(reinterpret_cast<const char*>(img + (s_width * (s_height - i - 1))), width);

      // Add padding if necessary (rows must multiple of 4)
      int paddingSize = 4 - (width % 4);
      if (paddingSize != 4)
        outfile.write(reinterpret_cast<const char*>(padding), paddingSize);
    }

    delete[] img;
    outfile.close();

    std::cout << "8-bit BMP successfully created" << std::endl;

    return true;
  }

  // This function splits the value parameter into 4 bytes, and then inserts
  // the bytes into the given byte pointer.
  void BMP8Out::insertIntAsBytes(unsigned char* start, int value)
  {
    start[0] = (unsigned char)(value);
    start[1] = (unsigned char)(value >> 8);
    start[2] = (unsigned char)(value >> 16);
    start[3] = (unsigned char)(value >> 24);
  }

}