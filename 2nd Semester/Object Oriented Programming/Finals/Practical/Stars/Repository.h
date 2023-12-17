//
// Created by Mircea Maierean on 12.06.2023.
//

#ifndef STARS_REPOSITORY_H
#define STARS_REPOSITORY_H

#include "Star.h"
#include "Astronaut.h"
#include <string>
#include <fstream>
#include <set>
#include <vector>

class Repository {
private:
    std::vector <Astronaut> astronauts;
    std::vector <Star> stars;
    std::string astronautsFileName, starsFileName;
public:
    Repository(std::string astronautsFileName, std::string starsFileName)
    {
        this->astronautsFileName = astronautsFileName;
        this->starsFileName = starsFileName;
        this->loadStars();
        this->loadAstronauts();
    }
    ~Repository();
    void loadAstronauts();
    void loadStars();
    void addStar(const Star &star) { this->stars.push_back(star); }
    std::vector <Astronaut> &getAstronauts() { return this->astronauts; }
    std::vector <Star> &getStars() { return this->stars; }
};


#endif //STARS_REPOSITORY_H
