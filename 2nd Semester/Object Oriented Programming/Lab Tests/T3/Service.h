//
// Created by Mircea Maierean on 25.05.2023.
//

#ifndef T3_914MAIEREANMIRCEA_SERVICE_H
#define T3_914MAIEREANMIRCEA_SERVICE_H
#include "Repository.h"
#include <algorithm>

class Service
{
private:
    Repository repository;
public:
    std::vector <Document> getAllDocuments();
    std::vector <Document> getDocumentsBySearch(const std::string& searchAfter);
    std::string findBestMatch(const std::string& searchAfter);
};

#endif //T3_914MAIEREANMIRCEA_SERVICE_H
