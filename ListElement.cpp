#include "ListElement.h"
// void ListElement::changeKeyOrValue(Element* el) {
//             std::cout << "Do you want to change the key of element?\n";
//             std::cin >> s;
//             if (s == 'y') {
//                 std::cout << "Enter a key!\n";
//                 std::cin >> temp;
//                 el->setKey(temp);
//             }
//             std::cout << "Do you want to change the value of element?\n";
//             std::cin >> s;
//             if (s == 'y') {
//                 temp.erase();
//                 std::cout << "Enter a value!\n";
//                 std::cin >> temp;
//                 el->setValue(temp);
//             }
// }

const string ListElement::findWithKey(const string& key) const {
    char s;
    string temp;
    if (this->key == key) {
        return ("Key and value: " + key + ' ' + value);
    }
    for (Element* el : children) {
        if (el->getKey() == key) {
            std::cout << "Do you want to change the value of element?\n";
            std::cin >> s;
            if (s == 'y') {
                std::cout << "Enter a value!\n";
                std::cin >> temp;
                el->setValue(temp);
            }

            return ("Key and value: " + el->getKey() + ' ' + el->getValue());
        }
    }

    throw std::invalid_argument("There is no such a key!");
    

}

void ListElement::addChild(Element* elem) {
    this->children.push_back(elem);
}

vector<Element*> ListElement::getChildren() const {
    return this->children;
}

void ListElement::insertChildInFront(Element* toInsert) {
    children.insert(children.begin(), toInsert);
}

void ListElement::setKey(const string& key) {
    this->key = key;
}


void ListElement::print() const {
    
    std::cout << "List: " << key << ' ' << value << '\n';

    for (Element* el : this->children) {
        std::cout << " Has: ";
        el->print();
    }
}

ListElement::ListElement() = default;
ListElement::ListElement(const string& key, 
    const string& value) 
                        : Element(key, value) {} 

ListElement::ListElement(const ListElement& other) : Element(other) {
    children = other.children;
}


ListElement& ListElement::operator=(const ListElement& other) {
    if (this != &other) {
        children = other.children;
        Element::operator=(other);
    }

    return *this;
}


ListElement::~ListElement() {
    children.clear();
}