#include "../../include/ui/UI.h"
#include <iostream>
#include <string>

UI::UI()
{
  this->service = Service();
  this->service.generateRandomMovies();
}

UI::~UI()
{
}

void UI::printInitialMenu()
{
  std::cout << "Welcome to the Movie Management App!" << std::endl;
  std::cout << "1. Admin" << std::endl;
  std::cout << "2. User" << std::endl;
  std::cout << "3. Exit" << std::endl;
  std::cout << "Please enter your choice: ";
}

void UI::printAdminMenu()
{
  std::cout << "Welcome to the Admin Menu!" << std::endl;
  std::cout << "1. Add movie" << std::endl;
  std::cout << "2. Remove movie" << std::endl;
  std::cout << "3. Update movie" << std::endl;
  std::cout << "4. Print all movies" << std::endl;
  std::cout << "5. Exit" << std::endl;
}

void UI::printAllMovies()
{
  DynamicVector<Movie> movies = this->service.getMovies();
  std::cout << "Number of movies: " << movies.getSizeOfDynamicVector() << std::endl;
  for (int index = 0; index < movies.getSizeOfDynamicVector(); ++index)
    std::cout << index << ". " << movies[index].getTitle() << " " << movies[index].getGenre() << " " << movies[index].getTrailer() << " " << movies[index].getYearOfRelease() << " " << movies[index].getLikesCount() << std::endl;
}

void UI::adminAddMovie()
{
  std::string title, genre, trailer;
  int yearOfRelease, likesCount;
  std::cout << "Please enter the title of the movie: ";
  std::cin >> title;
  std::cout << "Please enter the genre of the movie: ";
  std::cin >> genre;
  std::cout << "Please enter the trailer of the movie: ";
  std::cin >> trailer;
  std::cout << "Please enter the year of release of the movie: ";
  std::cin >> yearOfRelease;
  std::cout << "Please enter the likes count of the movie: ";
  std::cin >> likesCount;
  Movie movie = Movie(title, genre, trailer, yearOfRelease, likesCount);
  try
  {
    movie.validateMovie();
  }
  catch (const std::exception &caughtException)
  {
    std::cout << "Invalid movie!. Please try again" << std::endl;
    return;
  }

  if (this->service.addMovie(movie))
    std::cout << "Movie added successfully!" << std::endl;
  else
    std::cout << "Movie already exists!" << std::endl;
}

void UI::adminRemoveMovie()
{
  this->printAllMovies();
  int positionOfMovie;
  std::cout << "Please enter the position of the movie you want to remove: ";
  std::cin >> positionOfMovie;
  if (this->service.removeMovieByPosition(positionOfMovie))
    std::cout << "Movie removed successfully!" << std::endl;
  else
    std::cout << "Movie does not exist!" << std::endl;
}

void UI::adminUpdateMovie()
{
  this->printAllMovies();
  int positionOfMovie;
  std::cout << "Please enter the position of the movie you want to update: ";
  std::cin >> positionOfMovie;
  std::cin.ignore();
  Movie movieToBeUpdated;
  try
  {
    movieToBeUpdated = this->service.getMovieByPosition(positionOfMovie);
  }
  catch (const std::exception &caughtException)
  {
    std::cout << "Invalid position!. Please try again\n";
    return;
  }
  std::string titleOfMovieToBeUpdated = movieToBeUpdated.getTitle(), genreOfMovieToBeUpdated = movieToBeUpdated.getGenre(), trailerOfMovieToBeUpdated = movieToBeUpdated.getTrailer(), readInput;
  int yearOfRelease = movieToBeUpdated.getYearOfRelease(), likesCount = movieToBeUpdated.getLikesCount();
  std::cout << "Please enter the title of the movie. If you do not want to update this field, just press enter: ";
  std::getline(std::cin, readInput); // read the newline character
  if (readInput != "")
    titleOfMovieToBeUpdated = readInput;
  std::cout << "Please enter the genre of the movie. If you do not want to update this field, just press enter: ";
  std::getline(std::cin, readInput); // read the newline character
  if (readInput != "")
    genreOfMovieToBeUpdated = readInput;
  std::cout << "Please enter the trailer of the movie: If you do not want to update this field, just press enter:  ";
  std::getline(std::cin, readInput); // read the newline character
  if (readInput != "")
    trailerOfMovieToBeUpdated = readInput;
  int integerField;
  std::cout << "Please enter the year of release of the movie. If you do not want to update this field, press 0: ";
  std::cin >> integerField;
  if (integerField != 0)
    yearOfRelease = integerField;
  std::cout << "Please enter the likes count of the movie. If you do not want to update this field, press 0: ";
  std::cin >> integerField;
  if (integerField != 0)
    likesCount = integerField;
  Movie updatedMovie = Movie(titleOfMovieToBeUpdated, genreOfMovieToBeUpdated, trailerOfMovieToBeUpdated, yearOfRelease, likesCount);
  try
  {
    updatedMovie.validateMovie();
  }
  catch (const std::exception &caughtException)
  {
    std::cout << "Invalid movie!. Please try again" << std::endl;
    return;
  }
  if (this->service.updateMovie(positionOfMovie, updatedMovie))
    std::cout << "Movie updated successfully!" << std::endl;
  else
    std::cout << "Movie does not exist!" << std::endl;
}

void UI::runApp()
{
  this->printInitialMenu();
  int choice = 0;
  std::cout << "Please enter your choice: ";
  std::cin >> choice;
  if (choice == 1)
    this->service.setAdminCredentials(true);
  else if (choice == 2)
    this->service.setAdminCredentials(false);
  else if (choice == 3)
  {
    std::cout << "Thank you for using the Movie Management App!" << std::endl;
    return;
  }
  while (true)
  {
    if (this->service.getMoviesCount() == 0)
    {
      std::cout << "There are no movies in the database!" << std::endl;
      break;
    }
    if (this->service.getAdminCredentials())
    {
      this->printAdminMenu();
      std::cout << "Please enter your choice: ";
      std::cin >> choice;
      if (choice == 1)
        this->adminAddMovie();
      else if (choice == 2)
        this->adminRemoveMovie();
      else if (choice == 3)
        this->adminUpdateMovie();
      else if (choice == 4)
        this->printAllMovies();
      else if (choice == 5)
        break;
    }
    else
    {
      std::cout << "Stay tuned for the user menu!\n";
      break;
    }
  }
  std::cout << "Thank you for using the Movie Management App!" << std::endl;
}