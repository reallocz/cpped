#pragma once
#include <string>
#include "core/string.h"

class Document {

public:
    Document();
    virtual ~Document();
    void insert(char c);

    friend std::ostream& operator<<(std::ostream& o, const Document& d);


private:
    std::string _filename;
    unsigned int _curline;  // Cursor line
    String _lines[4];
};
