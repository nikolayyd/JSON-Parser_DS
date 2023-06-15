#include <iostream>
#include "Tokenizer.h"

int main(int argc, char const *argv[])
{
    
    string nameOfFile = "test1.json";
    // std::ifstream in(nameOfFile);

    Tokenizer first;
    first.startProgram(nameOfFile);
    


    // I read the keys and values with the "", because of that i do this:
    string searchedKey;
    searchedKey.push_back('"');
    searchedKey.append("id");
    searchedKey.push_back('"');

    // string searchedObj = c.findWithKey(searchedKey);

    // std::cout << searchedObj << '\n';
    return 0;
}
