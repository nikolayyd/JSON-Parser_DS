#pragma once
#include <string>
#include <fstream>
#include <exception>
#include <iostream>
#include <vector>

using std::string;
using std::vector;

class Element {
protected:
    string key;
    string value;

public:
    virtual void print() const = 0;
public:
    Element() = default;
    Element(const string& key, const string& value) : key(key), value(value) {}

    Element(const Element& other) : key(other.key), value(other.value) {}
    Element& operator=(const Element& other) {
        if (this != &other) {
            key = other.key;
            value = other.value;
        }

        return *this;
    }

    virtual ~Element() {
        key.clear();
        value.clear();
    }

    const string getKey() const {
        return key;
    }

    const string getValue() const {
        return value;
    }

    void setValue(const string& value) {
        this->value = value;
    }

    void setKey(const string& key) {
        this->key = key;
    }
};