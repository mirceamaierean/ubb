#include "FileWatchList.h"
#include <fstream>

void FileWatchList::openInApp() const
{
  this->writeToFile();
  std::string commandToOpenFile = "open " + this->fileName;
  system(commandToOpenFile.c_str());
}
