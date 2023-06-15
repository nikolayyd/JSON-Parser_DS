#pragma once
#include "Element.h"

class LeafElement : public Element {
public:
    LeafElement();
    LeafElement(const string& key, const string& value);
    LeafElement(const LeafElement& other);
    LeafElement& operator=(const LeafElement& other);
    ~LeafElement();

public:
    virtual void print() const override;
};