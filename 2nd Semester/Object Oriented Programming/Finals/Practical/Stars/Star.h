//
// Created by Mircea Maierean on 12.06.2023.
//

#ifndef STARS_STAR_H
#define STARS_STAR_H
#include <iostream>

class Star
{
private:
    std::string name, constellation;
    int ra;
    double dec;
public:
    explicit Star(std::string name = "", std::string constellation = "", int ra = 0, double dec = 0) : name{name},
                                                                                                        constellation{constellation},
                                                                                                        ra{ra},
                                                                                                        dec{dec} {};
    [[nodiscard]] std::string getName() const { return this->name; }
    [[nodiscard]] std::string getConstellation() const { return this->constellation; }
    [[nodiscard]] int getRa() const { return this->ra; }
    [[nodiscard]] double getDec() const { return this->dec; }
    inline bool operator < (const Star &other) const
    {
        return this->constellation < other.constellation;
    }
};

#endif //STARS_STAR_H
