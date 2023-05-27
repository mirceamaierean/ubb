#include "Song.h"

Song::Song() : title(""), artist(""), duration(Duration()), source("") {}

Song::Song(const std::string &artist, const std::string &title, const Duration &duration, const std::string &source)
{
	this->artist = artist;
	this->title = title;
	this->duration = duration;
	this->source = source;
}

void Song::play()
{
	system(("open " + this->source).c_str());
}