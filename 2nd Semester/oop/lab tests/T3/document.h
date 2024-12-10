//
// Created by Mircea Maierean on 25.05.2023.
//

#ifndef T3_914MAIEREANMIRCEA_DOCUMENT_H
#define T3_914MAIEREANMIRCEA_DOCUMENT_H
#include <iostream>
#include <utility>

class Document
{
private:
    std::string name, listOfKeywords, content;
public:
    explicit Document(std::string name = "", std::string listOfKeywords = "", std::string content = "") : name{std::move(name)}, listOfKeywords{std::move(listOfKeywords)}, content{content} {};
    [[nodiscard]] std::string getName() const { return this->name; };
    [[nodiscard]] std::string getListOfKeywords() const { return this->listOfKeywords; };
    inline bool operator < (const Document &other) const { return this->name < other.getName(); }
    std::string toString() { return this->name + " | " + this->listOfKeywords; }
};

#endif //T3_914MAIEREANMIRCEA_DOCUMENT_H
