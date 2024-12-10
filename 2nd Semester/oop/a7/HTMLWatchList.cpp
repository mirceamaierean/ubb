#include "HTMLWatchList.h"
#include "Exceptions.h"
#include <fstream>

void HTMLWatchList::writeToFile() const
{
  std::ofstream HTMLOutputFile(this->fileName.c_str());

  if (!HTMLOutputFile.is_open())
    throw FileException("The HTML file could not be opened!");

  HTMLOutputFile << "<!DOCTYPE html> <html> <head> <title> Movie WatchList</title> </head > <body> <table border=\"1\">";
  HTMLOutputFile << "<tr> <td> Index </td> <td> Title </td> <td> Genre </td> <td> Year Of Release </td> <td> Likes Count </td> <td> Trailer </td> </tr>";
  int index = 0;
  for (auto movie : this->movies)
    HTMLOutputFile << "<tr> <td>" << index++ << "</td> <td>" << movie.getTitle() << "</td> <td>" << movie.getGenre() << "</td> <td>" << movie.getYearOfRelease() << "</td> <td>" << movie.getLikesCount() << "</td> <td><a href=\"" << movie.getTrailer() << "\"> Link</a></ td> </tr>";

  HTMLOutputFile << "</table> </body> </html>";

  HTMLOutputFile.close();
}