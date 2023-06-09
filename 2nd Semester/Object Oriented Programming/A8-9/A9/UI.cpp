#include "UI.h"
#include <iostream>
#include <string>
#include "Exceptions.h"
#include "CSVWatchList.h"
#include "HTMLWatchList.h"
#include "FileRepository.h"

using namespace OPTIONS;

UI::UI()
{
  this->service = Service();
  this->chooseStorageType();
  this->choseFileTypeWatchList();
}

void UI::chooseStorageType()
{
  this->service.setTypeOfRepository(new FileRepository{STORAGE_TYPE::STORAGE_FILE_NAME});
}

void UI::choseFileTypeWatchList()
{
  while (true)
  {
    std::cout << "Please choose the type of file you want to use for the watchlist!\n";
    std::cout << "1. CSV\n";
    std::cout << "2. HTML\n";
    std::cout << "Please enter your choice: ";
    std::string choice;
    std::cin >> choice;
    if (choice == FILE_TYPE::CSV)
    {
      this->service.setTypeOfWatchList(new CSVWatchList{"CSVWatchList.csv"});
      return;
    }
    else if (choice == FILE_TYPE::HTML)
    {
      this->service.setTypeOfWatchList(new HTMLWatchList{"HTMLWatchList.html"});
      return;
    }
    else
      std::cout << "Invalid choice! Try again\n";
  }
}

void UI::printInitialMenu()
{
  std::cout << "Welcome to the Movie Management App!\n";
  std::cout << "1. Admin\n";
  std::cout << "2. User\n";
  std::cout << "3. Exit\n";
  std::cout << "Please enter your choice: ";
}

void UI::printAdminMenu()
{
  std::cout << "Welcome to the Admin Menu!\n";
  std::cout << "1. Add movie\n";
  std::cout << "2. Remove movie\n";
  std::cout << "3. Update movie\n";
  std::cout << "4. Print all movies\n";
  std::cout << "5. Switch to user interface\n";
  std::cout << "6. Exit\n";
}

void UI::printUserMenu()
{
  std::cout << "Welcome to the User Menu!\n";
  std::cout << "1. Get movies by genre\n";
  std::cout << "2. Display watchlist\n";
  std::cout << "3. Delete a movie from the watchlist\n";
  std::cout << "4. Switch to admin interface\n";
  std::cout << "5. Exit\n";
}

void UI::printAllMovies()
{
  std::vector<Movie> movies = this->service.getMovies();
  std::cout << "Number of movies: " << movies.size() << "\n";
  std::vector<Movie>::iterator iteratorUsedForPrintingMovies = movies.begin();
  for (; iteratorUsedForPrintingMovies != movies.end(); ++iteratorUsedForPrintingMovies)
  {
    Movie currentMovie = *iteratorUsedForPrintingMovies;
    std::cout << std::distance(movies.begin(), iteratorUsedForPrintingMovies) << ". " << currentMovie << "\n";
  }
}

void UI::adminAddMovie()
{
  std::cout << "Please enter the details of the movie you want to add! Be careful, the format is important!\nThe format is: title | genre | year of release | trailer | likesCount\n";
  std::cin.ignore();
  Movie movieToAdd;
  try
  {
    std::cin >> movieToAdd;
  }
  catch (MovieExceptions &errorsCaught)
  {
    std::cout << "There were some errors, try again!\n";
    for (const auto &errorCaught : errorsCaught.returnErrors())
      std::cout << errorCaught.what() << "\n";
    return;
  }
  try
  {
    this->service.addMovie(movieToAdd);
  }
  catch (DuplicateMovieException &caughtException)
  {
    std::cout << caughtException.what() << "\n";
    return;
  }
  catch (RepositoryException &caughtException)
  {
    std::cout << caughtException.what() << "\n";
    return;
  }
}

void UI::adminRemoveMovie()
{
  this->printAllMovies();
  int positionOfMovie;
  std::cout << "Please enter the position of the movie you want to remove: ";
  std::cin >> positionOfMovie;
  try
  {
    this->service.removeMovieByPosition(positionOfMovie);
  }
  catch (RepositoryException &caughtException)
  {
    std::cout << caughtException.what() << "\n";
    return;
  }
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
  catch (InvalidPositionException &caughtException)
  {
    std::cout << caughtException.what() << "\n";
    return;
  }

  std::string titleOfMovieToBeUpdated = movieToBeUpdated.getTitle(),
              genreOfMovieToBeUpdated = movieToBeUpdated.getGenre(),
              trailerOfMovieToBeUpdated = movieToBeUpdated.getTrailer(),
              yearOfRelease = std::to_string(movieToBeUpdated.getYearOfRelease()),
              likesCount = std::to_string(movieToBeUpdated.getLikesCount()),
              readInput;

  std::cout << "Please enter the title of the movie. If you do not want to update this field, just press enter: ";
  std::getline(std::cin, readInput); // read the newline character
  if (readInput != "")
    titleOfMovieToBeUpdated = readInput;

  std::cout << "Please enter the genre of the movie. If you do not want to update this field, just press enter: ";
  std::getline(std::cin, readInput); // read the newline character
  if (readInput != "")
    genreOfMovieToBeUpdated = readInput;

  std::cout << "Please enter the trailer of the movie: If you do not want to update this field, just press enter: ";
  std::getline(std::cin, readInput); // read the newline character
  if (readInput != "")
    trailerOfMovieToBeUpdated = readInput;

  std::cout << "Please enter the year of release of the movie. If you do not want to update this field, just press enter: ";
  std::getline(std::cin, readInput); // read the newline character
  if (readInput != "")
    yearOfRelease = readInput;

  std::cout << "Please enter the likes count of the movie. If you do not want to update this field, just press enter: ";
  std::getline(std::cin, readInput); // read the newline character
  if (readInput != "")
    likesCount = readInput;

  Movie updatedMovie;
  try
  {
    MovieValidator::validateMovieIdentifiers(titleOfMovieToBeUpdated, genreOfMovieToBeUpdated, yearOfRelease, trailerOfMovieToBeUpdated, likesCount);
    updatedMovie.setTitle(titleOfMovieToBeUpdated);
    updatedMovie.setGenre(genreOfMovieToBeUpdated);
    updatedMovie.setYearOfRelease(std::stoi(yearOfRelease));
    updatedMovie.setTrailer(trailerOfMovieToBeUpdated);
    updatedMovie.setLikesCount(std::stoi(likesCount));
  }
  catch (MovieExceptions &errorsCaught)
  {
    std::cout << "There were some errors regarding user input, try again!\n";
    for (const auto &errorCaught : errorsCaught.returnErrors())
      std::cout << errorCaught.what() << "\n";
    return;
  }

  try
  {
    this->service.updateMovie(positionOfMovie, updatedMovie);
  }
  catch (InvalidPositionException &caughtException)
  {
    std::cout << caughtException.what() << "\n";
    return;
  }
  catch (DuplicateMovieException &caughtException)
  {
    std::cout << caughtException.what() << "\n";
    return;
  }
}

void UI::userGetMoviesByGenre()
{
  std::string genreOfMovieThatTheUserIsSearchingAfterInOrderToAddToHisWishlist;
  std::cin.ignore();
  std::cout << "Please enter the genre of the movies you want to see: ";
  std::getline(std::cin, genreOfMovieThatTheUserIsSearchingAfterInOrderToAddToHisWishlist);

  std::vector<Movie> moviesWithGivenGenre = this->service.getMoviesByGenre(genreOfMovieThatTheUserIsSearchingAfterInOrderToAddToHisWishlist);
  if (moviesWithGivenGenre.size() == 0)
  {
    std::cout << "There are no movies with the given genre!\n";
    return;
  }
  bool checkIfThereAreMoreMovies = true;
  while (checkIfThereAreMoreMovies)
  {
    checkIfThereAreMoreMovies = false;
    for (auto movie : moviesWithGivenGenre)
    {
      try
      {
        this->service.checkIfMovieIsAlreadyInThePlaylist(movie);
        checkIfThereAreMoreMovies = true;
        std::cout << "Title: " << movie.getTitle() << "\n";
        std::cout << "Genre: " << movie.getGenre() << "\n";
        std::cout << "Year of Release: " << movie.getYearOfRelease() << "\n";
        std::cout << "Likes Count: " << movie.getLikesCount() << "\n";
        movie.openTrailerInBrowser();
        std::cout << "Do you want to add this movie to your wishlist? (y/n): ";
        char choiceOfUser;
        std::cin >> choiceOfUser;
        choiceOfUser = std::tolower(choiceOfUser);
        if (choiceOfUser == 'y')
          this->service.addMovieToWatchList(movie);
        else
          std::cout << "Movie not added to your wishlist!\n";
        std::cout << "Do you want to see the next movie? (y/n): ";
        std::cin >> choiceOfUser;
        if (choiceOfUser == 'n')
        {
          std::cout << "That's it! You can still search for other movies!\n";
          return;
        }
      }
      catch (DuplicateMovieException &caughtException)
      {
      }
    }
  }
  std::cout << "That's it! We do not have any other movies with your desired genre! Enjoy your bingewatching!\n";
}

void UI::userDisplayMoviesFromWatchList()
{
  try
  {
    this->service.displayPlaylist();
  }
  catch (FileException &caughtException)
  {
    std::cerr << caughtException.what() << '\n';
  }
}

void UI::userDeleteMovieFromWatchList()
{
  this->userDisplayMoviesFromWatchList();
  std::vector<Movie> moviesFromWatchList = this->service.getMoviesFromWatchList();
  if (moviesFromWatchList.size() == 0)
    return;
  int positionOfMovieToBeDeleted;
  std::cout << "Please enter the position of the movie you want to delete from your watchlist: ";
  std::cin >> positionOfMovieToBeDeleted;
  std::cout << "Did you like the movie? (y/n): ";
  char choiceOfUser;
  std::cin >> choiceOfUser;
  choiceOfUser = tolower(choiceOfUser);
  if (choiceOfUser == 'y')
  {
    try
    {
        this->service.increaseLikesCountOfMovie(moviesFromWatchList[positionOfMovieToBeDeleted]);
      std::cout << "Likes count increased successfully!\n";
    }
    catch (const std::exception &e)
    {
      std::cout << "Invalid position!\n";
      return;
    }
  }
  this->service.removeWatchedMovieFromWatchList(positionOfMovieToBeDeleted, false);
  std::cout << "Movie deleted successfully!\n";
}

void UI::runApp()
{
  this->printInitialMenu();
  std::string choice;
  std::cin >> choice;
  if (choice == INTERFACE::ADMIN)
    this->service.setAdminCredentials(true);
  else if (choice == INTERFACE::USER)
    this->service.setAdminCredentials(false);
  else if (choice == EXIT_APPLICATION)
  {
    std::cout << "Thank you for using the Movie Management App!\n";
    return;
  }
  while (true)
  {
    if (this->service.getAdminCredentials())
    {
      this->printAdminMenu();
      std::cout << "Please enter your choice: ";
      std::cin >> choice;
      if (choice == ADMIN::ADD_MOVIE)
        this->adminAddMovie();
      else if (choice == ADMIN::REMOVE_MOVIE)
        this->adminRemoveMovie();
      else if (choice == ADMIN::UPDATE_MOVIE)
        this->adminUpdateMovie();
      else if (choice == ADMIN::PRINT_ALL_MOVIES)
        this->printAllMovies();
      else if (choice == ADMIN::SWITCH_TO_USER_INTERFACE)
        this->service.setAdminCredentials(false);
      else if (choice == ADMIN::EXIT)
        break;
    }
    else
    {
      this->printUserMenu();
      std::cout << "Please enter your choice: ";
      std::cin >> choice;
      if (choice == USER::GET_MOVIES_BY_GENRE)
        this->userGetMoviesByGenre();
      else if (choice == USER::DISPLAY_WATCHLIST)
        this->userDisplayMoviesFromWatchList();
      else if (choice == USER::DELETE_MOVIE_FROM_WATCHLIST)
        this->userDeleteMovieFromWatchList();
      else if (choice == USER::SWITCH_TO_ADMIN_INTERFACE)
        this->service.setAdminCredentials(true);
      else if (choice == USER::EXIT)
        break;
    }
  }
  std::cout << "Thank you for using the Movie Management App!\n";
}
