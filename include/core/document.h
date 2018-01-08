#pragma once
#include <string>
#include "core/line.h"
#include "core/doccmd.h"

#define DDEF_FILENAME "document.txt"

// All communication's with a Document are done through a command
class Document
{

public:
    Document();
    virtual ~Document();
    void exec(Doccmd cmd);

    friend std::ostream& operator<<(std::ostream& o, const Document& d);

private:
    void save();

private:
    std::string _filename;
    unsigned int _curline;  // Cursor line
    unsigned int _curcol;   // Cursor col
};
