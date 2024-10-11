//
// Created by Mircea Maierean on 25.05.2023.
//

#ifndef T3_914MAIEREANMIRCEA_REPOSITORY_H
#define T3_914MAIEREANMIRCEA_REPOSITORY_H
#include "document.h"
#include <vector>
#include <sstream>
#include <fstream>

class Repository
{
private:
    std::vector <Document> documents;
public:
    Repository() { this->loadRepo(); };
    void loadRepo();
    std::vector <Document> getAllDocuments() { return this->documents; };
};
#endif //T3_914MAIEREANMIRCEA_REPOSITORY_H
