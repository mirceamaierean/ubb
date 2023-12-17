//
// Created by Mircea Maierean on 13.06.2023.
//

#ifndef PROGREMR_ISSUE_H
#define PROGREMR_ISSUE_H

#include <iostream>

class Issue{
private:
    std::string description, reporter, solver;
    bool isOpen;
public:
    Issue(std::string description = "", bool isOpen = false, std::string reporter = "", std::string solver = "") : description{description},
                                                                                                                    isOpen{isOpen},
                                                                                                                    reporter{reporter},
                                                                                                                    solver{solver} {};
    std::string getDescription() const
    {
        return this->description;
    }
    std::string getReporter() const
    {
        return this->reporter;
    }
    std::string getSolver() const
    {
        return this->solver;
    }
    bool getIsOpen() const
    {
        return this->isOpen;
    }
    std::string formatAsString() const
    {
        return this->description + "|" + (isOpen ? "open" : "closed") + "|" + this->reporter + "|" + this->solver;
    }

    void setSolver(std::string solver) { this->solver = solver; }

    void setIsOpen(bool isOpen) { this->isOpen = isOpen; }

    inline bool operator < (const Issue &other) const
    {
        if (this->isOpen == other.isOpen)
            return this->description < other.description;
        return this->isOpen < other.isOpen;
    }
};

#endif //PROGREMR_ISSUE_H
