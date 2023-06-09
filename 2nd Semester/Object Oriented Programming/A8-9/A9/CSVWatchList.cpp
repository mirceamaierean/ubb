#include "CSVWatchList.h"
#include "Exceptions.h"
#include <fstream>

void CSVWatchList::writeToFile() const {
    std::ofstream CSVOutputFile(this->fileName.c_str());

    if (!CSVOutputFile.is_open())
        throw FileException("The CSV file could not be opened!");

    CSVOutputFile << "Index, Name, Genre, Year Of Release, Trailer, Likes Count\n";
    int index = 0;
    for (auto movie: this->movies)
        CSVOutputFile << index++ << ", " << movie.getTitle() << "," << movie.getGenre() << ","
                      << movie.getYearOfRelease() << "," << movie.getTrailer() << "," << movie.getLikesCount() << "\n";

    CSVOutputFile.close();
}