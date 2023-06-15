#pragma once
#include "Element.h"
class ListElement : public Element {
private:
    vector<Element*> children;

public:
    // void changeKeyOrValue(Element* el);
    void addChild(Element* elem);
    vector<Element*> getChildren() const; 
    virtual void print() const override;
    void insertChildInFront(Element* toInsert);
    void setKey(const string& key);
    const string findWithKey(const string& key) const;
public:
    ListElement();
    ListElement(const string& key, const string& value);
    ListElement(const ListElement& other);
    ListElement& operator=(const ListElement& other);
    ~ListElement();



};