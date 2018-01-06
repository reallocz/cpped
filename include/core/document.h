#pragma once
#include <string>
#include "core/line.h"

class Document {

public:
    Document();
    virtual ~Document();
    void insert(char c);

    friend std::ostream& operator<<(std::ostream& o, const Document& d);


private:
    std::string _filename;
    unsigned int _curline;  // Cursor line
    Line _lines[4];
};
