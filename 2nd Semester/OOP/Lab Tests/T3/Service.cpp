//
// Created by Mircea Maierean on 25.05.2023.
//

#include "Service.h"

std::vector <Document> Service::getAllDocuments()
{
    std::vector <Document> documents = this->repository.getAllDocuments();
    std::sort(documents.begin(), documents.end());
    return documents;
}

std::vector <Document> Service::getDocumentsBySearch(const std::string& searchAfter)
{
    std::vector <Document> documentsFiltered;
    for (const auto& document : this->getAllDocuments())
        if (document.getName().find(searchAfter) != std::string::npos || document.getListOfKeywords().find(searchAfter) != std::string::npos)
            documentsFiltered.push_back(document);
    return documentsFiltered;
}

std::string Service::findBestMatch(const std::string& searchAfter) {
    std::string bestString;
    for (const auto& document : this->getAllDocuments())
        if (document.getName().find(searchAfter) != std::string::npos)
        {
            if (bestString.empty() || bestString.length() > document.getName().length())
                bestString = document.getName();
        }
    if (bestString.empty())
        bestString = "There is no such name in the list";
    return bestString;
}