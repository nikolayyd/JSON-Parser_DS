#include "LeafElement.h"

void LeafElement::print() const {
    
    std::cout << "Leaf: " << key << ' ' << value << '\n';
}

LeafElement::LeafElement() : Element() {}

LeafElement::LeafElement(const string& key, const string& value) : 
    Element(key, value) {}

LeafElement::LeafElement(const LeafElement& other) : Element(other) {}

LeafElement& LeafElement::operator=(const LeafElement& other) {
    Element::operator=(other);
    return *this;
}


LeafElement::~LeafElement() {}