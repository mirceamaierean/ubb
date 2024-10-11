#pragma once
#include "FileWatchList.h"

class CSVWatchList : public FileWatchList
{
public:
  CSVWatchList(const std::string &fileName) : FileWatchList{fileName} {}
  void writeToFile() const override;
};