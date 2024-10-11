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
  std::cout << "5. Exit\n";
}

void UI::printUserMenu()
{
  std::cout << "Welcome to the User Menu!\n";
  std::cout << "1. Get movies by genre\n";
  std::cout << "2. Display watchlist\n";
  std::cout << "3. Delete a movie from the watchlist\n";
  std::cout << "4. Exit\n";
}

void UI::printAllMovies()
{
  std::vector<Movie> movies = this->service.getMovies();
  std::cout << "Number of movies: " << movies.size() << "\n";
  std::vector<Movie>::iterator iteratorUsedForPrintingMovies = movies.begin();
  for (; iteratorUsedForPrintingMovies != movies.end(); ++iteratorUsedForPrintingMovies)
  {
    Movie currentMovie = *iteratorUsedForPrintingMovies;
    std::cout
        << std::distance(movies.begin(), iteratorUsedForPrintingMovies) << ". " << currentMovie.getTitle() << " " << currentMovie.getGenre() << " " << currentMovie.getTrailer() << " " << currentMovie.getYearOfRelease() << " " << currentMovie.getLikesCount() << "\n";
  }
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
    std::cout << "Invalid movie Please try again\n";
    return;
  }

  if (this->service.addMovie(movie))
    std::cout << "Movie added successfully!\n";
  else
    std::cout << "Movie already exists!\n";
}

void UI::adminRemoveMovie()
{
  this->printAllMovies();
  int positionOfMovie;
  std::cout << "Please enter the position of the movie you want to remove: ";
  std::cin >> positionOfMovie;
  if (this->service.removeMovieByPosition(positionOfMovie))
    std::cout << "Movie removed successfully!\n";
  else
    std::cout << "Movie does not exist!\n";
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
    std::cout << "Invalid position! Please try again\n";
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
    std::cout << "Invalid movie Please try again\n";
    return;
  }
  if (this->service.updateMovie(positionOfMovie, updatedMovie))
    std::cout << "Movie updated successfully!\n";
  else
    std::cout << "Movie does not exist!\n";
}

void UI::userGetMoviesByGenre()
{
  std::string genreOfMovieThatTheUserIsSearchingAfterInOrderToAddToHisWishlist;
  std::cin.ignore();
  std::cout << "Please enter the genre of the movies you want to see: ";
  std::getline(std::cin, genreOfMovieThatTheUserIsSearchingAfterInOrderToAddToHisWishlist);
  std::vector<int> vectorOfIndexesOfMovies = this->service.getPositionsOfMoviesByGenre(genreOfMovieThatTheUserIsSearchingAfterInOrderToAddToHisWishlist);
  if (vectorOfIndexesOfMovies.size() == 0)
  {
    std::cout << "There are no movies with the given genre!\n";
    return;
  }
  std::vector<int>::iterator iteratorOfVectorOfIndexesOfMovies = vectorOfIndexesOfMovies.begin();
  while (iteratorOfVectorOfIndexesOfMovies != vectorOfIndexesOfMovies.end())
  {
    Movie movieThatIsCurrentlyDisplayes = this->service.getMovieByPosition(*iteratorOfVectorOfIndexesOfMovies);
    std::cout << "Title: " << movieThatIsCurrentlyDisplayes.getTitle() << "\n";
    std::cout << "Genre: " << movieThatIsCurrentlyDisplayes.getGenre() << "\n";
    std::cout << "Year of Release: " << movieThatIsCurrentlyDisplayes.getYearOfRelease() << "\n";
    std::cout << "Likes Count: " << movieThatIsCurrentlyDisplayes.getLikesCount() << "\n";
    this->service.openTrailerOfMovieInBrowser(*iteratorOfVectorOfIndexesOfMovies);
    std::cout << "Do you want to add this movie to your wishlist? (y/n): ";
    char choiceOfUser;
    std::cin >> choiceOfUser;
    choiceOfUser = tolower(choiceOfUser);
    if (choiceOfUser == 'y')
    {
      this->service.addIndexOfMovieToUserListByPosition(*iteratorOfVectorOfIndexesOfMovies);
      std::cout << "Movie added to your wishlist!\n";
      iteratorOfVectorOfIndexesOfMovies = vectorOfIndexesOfMovies.erase(iteratorOfVectorOfIndexesOfMovies);
      --iteratorOfVectorOfIndexesOfMovies;
    }
    else
      std::cout << "Movie not added to your wishlist!\n";
    std::cout << "Do you want to see the next movie? (y/n): ";
    std::cin >> choiceOfUser;
    choiceOfUser = tolower(choiceOfUser);
    if (choiceOfUser == 'y')
    {
      ++iteratorOfVectorOfIndexesOfMovies;
      if (iteratorOfVectorOfIndexesOfMovies == vectorOfIndexesOfMovies.end())
        iteratorOfVectorOfIndexesOfMovies = vectorOfIndexesOfMovies.begin();
    }
    else
      break;
  }
  std::cout << "That's it! You can still search for other movies!\n";
}

void UI::userDisplayMoviesFromWatchList()
{
  std::vector<int> vectorOfIndexesOfMovies = this->service.getIndexesOfMoviesThatTheUserLikes();
  if (vectorOfIndexesOfMovies.size() == 0)
  {
    std::cout << "There are no movies in your wishlist!\n";
    return;
  }
  for (auto indexOfCurrentMovieToBeDisplayed : vectorOfIndexesOfMovies)
  {
    Movie currentMovieToBeDisplayed = this->service.getMovieByPosition(indexOfCurrentMovieToBeDisplayed);
    std::cout << currentMovieToBeDisplayed.getTitle() << " " << currentMovieToBeDisplayed.getGenre() << " " << currentMovieToBeDisplayed.getYearOfRelease() << " " << currentMovieToBeDisplayed.getLikesCount() << "\n";
  }
}

void UI::userDeleteMovieFromWatchList()
{
  this->userDisplayMoviesFromWatchList();
  std::vector<int> vectorOfIndexesOfMovies = this->service.getIndexesOfMoviesThatTheUserLikes();
  if (vectorOfIndexesOfMovies.size() == 0)
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
    this->service.increaseLikesCountOfMovieByPosition(vectorOfIndexesOfMovies[positionOfMovieToBeDeleted]);
    std::cout << "Likes count increased successfully!\n";
  }
  this->service.removeIndexOfMovieFromUserList(positionOfMovieToBeDeleted);
  std::cout << "Movie deleted successfully!\n";
}

void UI::runApp()
{
  this->printInitialMenu();
  int choice = 0;
  std::cout << "Please enter your choice: ";
  std::cin >> choice;
  if (choice == this->ADMIN_INTERFACE)
    this->service.setAdminCredentials(true);
  else if (choice == this->USER_INTERFACE)
    this->service.setAdminCredentials(false);
  else if (choice == this->EXIT_APPLICATION)
  {
    std::cout << "Thank you for using the Movie Management App!\n";
    return;
  }
  while (true)
  {
    if (this->service.getMoviesCount() == 0)
    {
      std::cout << "There are no movies in the database!\n";
      break;
    }
    if (this->service.getAdminCredentials())
    {
      this->printAdminMenu();
      std::cout << "Please enter your choice: ";
      std::cin >> choice;
      if (choice == this->ADMIN_ADD_MOVIE)
        this->adminAddMovie();
      else if (choice == this->ADMIN_REMOVE_MOVIE)
        this->adminRemoveMovie();
      else if (choice == this->ADMIN_UPDATE_MOVIE)
        this->adminUpdateMovie();
      else if (choice == this->ADMIN_PRINT_ALL_MOVIES)
        this->printAllMovies();
      else if (choice == this->ADMIN_EXIT)
        break;
    }
    else
    {
      this->printUserMenu();
      std::cout << "Please enter your choice: ";
      std::cin >> choice;
      if (choice == this->USER_GET_MOVIES_BY_GENRE)
        this->userGetMoviesByGenre();
      else if (choice == this->USER_DISPLAY_WATCHLIST)
        this->userDisplayMoviesFromWatchList();
      else if (choice == this->USER_DELETE_MOVIE_FROM_WATCHLIST)
        this->userDeleteMovieFromWatchList();
      else if (choice == this->USER_EXIT)
        break;
    }
  }
  std::cout << "Thank you for using the Movie Management App!\n";
}