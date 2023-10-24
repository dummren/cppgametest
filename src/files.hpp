#ifndef __FILES_HPP__
#define __FILES_HPP__

#include <filesystem>
#include <string>
#include <vector>

namespace Files {

  std::filesystem::path binPath();
  std::filesystem::path binDir();
  std::filesystem::path dataDir();

  std::string readFile(std::filesystem::path);
  std::string readDataFile(std::filesystem::path);
  std::vector<unsigned char> readBinaryFile(std::filesystem::path);

} // namespace Files

#endif // __FILES_HPP__
