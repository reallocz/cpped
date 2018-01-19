#pragma once
#include <string>
#include "core/line.h"
#include "core/doccmd.h"
#include "log.h"

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

    unsigned int numlines() const;
    const Line& operator[](unsigned int index);

private:
    void doubleLines();
    void resize();
    Line& currentLine();
    void setCurrentLine(unsigned int lineno);

    // Execs
    //void optimize(); // TODO
    void execInsertchar(Doccmd::Insertchar cmd);
    void execMove(Doccmd::Move cmd);
    void execEdit(Doccmd::Edit cmd);
    void execSave(Doccmd::Save cmd);

    void deleteLines();

private:
    std::string _filename;
    unsigned int _curline;  // Cursor line
    unsigned int _numlines;
    Line* _lines;
    Log _log{"Document"};
};
