#pragma once
#include <string>
#include "core/line.h"
#include "core/doccmd.h"

#define DDEF_FILENAME "document.txt"
#define DDEF_NUMLINES 2

// All communication's with a Document are done through a command
class Document
{

public:
    Document();
    virtual ~Document();
    void exec(Doccmd cmd);
    void print();

private:
    void doubleLines();
    void resize();
    //void optimize(); // TODO
    void execInsertchar(Doccmd::Insertchar cmd);
    void execMove(Doccmd::Move cmd);
    void execEdit(Doccmd::Edit cmd);
    void execSave(Doccmd::Save cmd);

private:
    std::string _filename;
    unsigned int _curline;  // Cursor line
    unsigned int _numlines;
    Line* _lines;
};
