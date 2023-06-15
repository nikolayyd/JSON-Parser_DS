#include "Tokenizer.h"
#include <iostream>

void Tokenizer::startProgram(const string& nameOfFile) {

    string expectedInput = "json-parser " + nameOfFile + " -find";
    string expectedInputShow = "json-parser " + nameOfFile;
    bool isRightCommand = false;

    std::ifstream jsonTest(nameOfFile);
    ListElement mainObj = this->tokenize(jsonTest);
    mainObj.print();

    do {
        string input;
        std::cout << "Enter a command!\n";
        std::getline(std::cin, input, '\n');
        
        string saveInput = input.substr(0, input.find_last_of(' '));
        string key = input.substr(input.find_last_of(' ') + 1, input.size());

        if (input == "exit") {
            return;
        }
        if (saveInput == expectedInput)
        {
            isRightCommand = true;
            std::cout << mainObj.findWithKey(key) << '\n';
        }
        if (saveInput == expectedInputShow && key == "-show") {
            isRightCommand = true;
            showJson(nameOfFile, mainObj);
        }

    } while (!isRightCommand);
}

void Tokenizer::showJson(const string& nameOfFile, const ListElement& mainObj) {
        mainObj.print();
        std::cout << "Size of obj: "<< mainObj.getChildren().size() << '\n';
}

void Tokenizer::removeWhiteSpaces(string &str)
{
    int count = 0;
    for (char s : str)
    {
        if (s == '"' || s == '{' || s == '[')
        {
            break;
        }
        count++;
    }

    string copy = str.substr(count, str.length());
    str.clear();
    str = copy;
}

string Tokenizer::tokenizeKey(string &str)
{
    string buffer;
    string key;

    for (char s : str)
    {
        if (s == ':')
        {
            key = buffer;
            break;
        }

        buffer += s;
    }
    // Check if it is ' : ' or ':'.

    if (key.back() == ' ')
    {
        key.pop_back();
    }

    // resize the temp string.

    
    // checking is it ' : ' or ':' between key and value.
    // we resize it to the last " because there are closing braces.
    if (str[key.length() + 1] == ':')
    {
        buffer = str.substr(key.length() + 2, str.find_last_of('"'));
    }
    else
    {
        buffer = str.substr(key.length() + 1, str.find_last_of('"'));
    }

    str.clear();
    str = buffer;
    removeWhiteSpaces(str);
    removeWhiteSpaces(key);

    return key;
}

string Tokenizer::tokenizeValue(string &str)
{
    string value;
    string buffer;

    //  Checking are "" written valid.
    bool arePair = true;
    for (char s : str)
    {
        if (s == '"')
        {

            if (arePair == true)
            {
                arePair = false;
            }
            else
            {
                arePair = true;
            }
        }

        value += s;
    }

    if (arePair == false)
    {
        throw std::invalid_argument ("Invalid input!");
    }

    // problem with '}' in the end
    value = value.substr(0, value.find_last_of('"') + 1);
    return value;
}

ListElement Tokenizer::tokenize(std::istream &in, bool isInCurrentObject)
{

    ListElement object;
    string temp;

    
    in.get();

    while (in.good()) {
        
        if (!isInCurrentObject)
        {
            break;
        }

        string key;
        string value;

        getline(in, temp, ',');
        
        removeWhiteSpaces(temp);

        // in tokenizeKey change temp and set the key!
        key = tokenizeKey(temp);

        if (temp.back() == '}' || temp.back() == ']') {
            isInCurrentObject = false;
        }

        // tokenize an object.

        if (temp.front() == '{')
        {

            // temporary is filled with key and value for one element.
            string tempKey;
            string tempValue;

            string copy = temp.substr(1, temp.length());
            temp = copy;
            removeWhiteSpaces(temp);
            tempKey = tokenizeKey(temp);
           
            ListElement obj;
           
            if (temp.front() != '{')
            {
                tempValue = tokenizeValue(temp);                  
                Element *toInsertLeaf = new LeafElement(tempKey, tempValue);
                obj = tokenize(in);
                obj.insertChildInFront(toInsertLeaf);
            } 
            
            // If there is object in object, first we add the elements in this object recursive
            // and then we set its key and insert in front the first element of it.
            // In final, we add this listElement into the object.
            else {
                ListElement newListElem = tokenize(in);
                newListElem.setKey(tempKey);
                temp = temp.substr(1, temp.length());
                tempKey = tokenizeKey(temp);
                tempValue = tokenizeValue(temp);
                Element* newLeafElem = new LeafElement(tempKey, tempValue);
                newListElem.insertChildInFront(newLeafElem);
                
                Element* childOfObject = new ListElement(newListElem);
                // std::cout << "Size of inner object: " << newListElem.getChildren().size() << '\n';
                obj.addChild(childOfObject);
            }

            obj.setKey(key);
            Element *child = new ListElement(obj);
            object.addChild(child);

            // std::cout << "Size of object: " << obj.getChildren().size() << '\n';
            temp.clear();
            continue;
        }

        // tokenize an array
        if (temp.front() == '[') {

            string tempKey = tokenizeKey(temp);
            string tempValue = tokenizeValue(temp);
            
            
            ListElement array = tokenize(in);

            Element* newElementForInsert = new LeafElement(tempKey,tempValue);
            
            array.insertChildInFront(newElementForInsert);
            Element* child = new ListElement(array);
            
            object.addChild(child);
            
            // std::cout << "Size of array: " << array.getChildren().size() << '\n';
            temp.clear();
            continue;
        }

        value = tokenizeValue(temp);

        Element *toInsert = new LeafElement(key, value);
        object.addChild(toInsert);

    }

    return object;   

}