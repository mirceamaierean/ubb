//
// Created by Mircea Maierean on 12.06.2023.
//

#ifndef STARS_SERVICE_H
#define STARS_SERVICE_H
#include "Repository.h"

class Service
{
private:
    Repository &repository;
public:
    explicit Service(Repository &repository) : repository{repository} {};
    std::vector<Astronaut> &getAstronauts() const { return this->repository.getAstronauts(); }
    std::vector<Star> &getStars() const { return this->repository.getStars();  }
    void addStar(const std::string &name, const std::string &constellation, const int &ra, const double &dec);
    std::vector<Star> getStarsFiltered(const std::string &name);
};

#endif //STARS_SERVICE_H
