#pragma once
#include "WatchList.h"

class FileWatchList : public WatchList
{
protected:
  std::string fileName;

public:
  FileWatchList(const std::string &fileName) : fileName{fileName} {}
  virtual void writeToFile() const = 0;
  void openInApp() const;
  virtual ~FileWatchList(){};
};