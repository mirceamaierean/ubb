//
// Created by Mircea Maierean on 12.06.2023.
//

#include "Service.h"

void Service::addStar(const std::string &name, const std::string &constellation, const int &ra, const double &dec)
{
    Star star{name, constellation, ra, dec};
    if (name.empty() || dec <= 0)
        throw std::exception();
    this->repository.addStar(star);
}

std::vector<Star> Service::getStarsFiltered(const std::string &name) {
    std::vector <Star> starsFiltered;
    for (auto &star : this->repository.getStars())
        if (star.getName().find(name) != std::string::npos)
            starsFiltered.push_back(star);
    return starsFiltered;
}
