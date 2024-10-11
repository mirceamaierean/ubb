#pragma once
#include "FileWatchList.h"

class HTMLWatchList : public FileWatchList
{
public:
  HTMLWatchList(const std::string &fileName) : FileWatchList{fileName} {}
  void writeToFile() const override;
};