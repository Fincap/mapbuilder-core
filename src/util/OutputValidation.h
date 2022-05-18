#pragma once
#include "APIExport.h"

#include <filesystem>
#include <string>

namespace mbc::util
{
  /*
  Helper function for validating the filepath provided by the caller to Output
  modules. If the directory to the filepath does not exist, then it will be
  created.
  filepath is passed by reference and may be directly modified in the case
  where validation errors are found.
  defaultFilename is the default name the module appends to the filepath in the
  case where the provided filepath is a directory.
  */
  void validateOutputFilepath(std::filesystem::path& filepath, std::string defaultFilename);

  inline void validateOutputFilepath(std::filesystem::path& filepath, std::string defaultFilename)
  {
    using namespace std::filesystem;

    /* Failsafe for when a filepath is provided with no extension and no
    separators. It will be treated as a directory by appending a separator and
    the default filename will be added to the given filepath. */
    if (filepath.stem() == filepath)
      filepath /= "";   // Overloaded /= to use system preferred sep.

    /* Check if output filepath has a filename. If it does; remove it for the
    next step of checking destination directory exists. If it doesnt; then
    append a default filename to the outputFilepath and continue on. */
    path outputDirectory(filepath);
    if (filepath.has_filename())
      outputDirectory.remove_filename();
    else
      filepath += defaultFilename;

    /* Check if output directory exists, if it doesn't then create it and all
    intermediate directories. */
    if (!exists(outputDirectory))
      create_directories(outputDirectory);
  }
}
