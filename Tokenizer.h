#pragma once
#include "LeafElement.h"
#include "ListElement.h"


class Tokenizer {
private:
    void removeWhiteSpaces(string& str);

    string tokenizeKey(string &str);

    string tokenizeValue(string& str);

public:
    ListElement tokenize(std::istream& in, bool isInCurrentObject = true);
    void startProgram(const string& nameOfFile);
    void showJson(const string& nameOfFile, const ListElement& mainObj);

public:

    Tokenizer() = default;
    Tokenizer(const Tokenizer& other) = delete;
    Tokenizer& operator=(const Tokenizer& other) = delete;
    ~Tokenizer() = default;
};