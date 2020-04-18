#pragma once

#include <string>
using std::string;

class Place {

    unsigned char id;
    string name;
    

public:
bool visited;
    Place();
    ~Place();

    void setId(unsigned char id);
    unsigned char getId() const;
    void setName(const string &name);
    string getName() const;
};
