#include "core/document.h"
#include <iostream>
#include <memory.h>

Document::Document()
{
    _filename = DDEF_FILENAME;
    _numlines = DDEF_NUMLINES;
    _curline = 0;

    _lines = new Line[_numlines];
}


Document::~Document()
{
    std::cout << "Document closed" << std::endl;
    delete[] _lines;
}

unsigned int Document::numlines() const
{
    return _numlines;
}


const Line& Document::operator[](unsigned int index) const
{
    if(index >= _numlines)
    {
        std::cout << "OUTOFBOUND line access in document: "
            << index << "/" << _numlines << std::endl;
        exit(1);
    }
    else
        return _lines[index];
}


void Document::doubleLines()
{
    std::cout << "Doubling lines: " << _numlines << " -> " << _numlines * 2 << std::endl;

    _numlines *= 2;
    resize();
}


void Document::resize()
{
    Line* newlines = new Line[_numlines];
    memset(newlines, 0, _numlines * sizeof(_lines[0]));
    memcpy(newlines, _lines, _numlines * sizeof(_lines[0]));
    delete[] _lines;
    _lines = newlines;
}

Line& Document::currentLine()
{
    Line& curline = _lines[_curline];
    curline.setactive(true);
    return curline;
}

void Document::setCurrentLine(unsigned int lineno)
{
    currentLine().setactive(false);
    _curline = lineno;
}

void Document::exec(Doccmd dcmd)
{
    switch (dcmd.type)
    {
    case Doccmd::Type::Insertchar:
        execInsertchar(dcmd.cmd.insertchar);
        break;
    case Doccmd::Type::Edit:
        execEdit(dcmd.cmd.edit);
        break;
    case Doccmd::Type::Move:
        execMove(dcmd.cmd.move);
        break;
    case Doccmd::Type::Save:
        execSave(dcmd.cmd.save);
        break;
    default:
        std::cout << "Default cmd" << std::endl;
        break;
    }
}


void Document::execInsertchar(Doccmd::Insertchar cmd)
{
    //std::cout << cmd.c << std::endl;
    Line& line = currentLine();
    line.insertChar(cmd.c);
}


void Document::execMove(Doccmd::Move cmd)
{
}


void Document::execEdit(Doccmd::Edit cmd)
{
    std::cout << "Edit" << std::endl;
}

// Save the doc to the fs
void Document::execSave(Doccmd::Save cmd)
{
    if(cmd.saveas)
        std::cout << "Saving As" << std::endl;
    else
        std::cout << "Saving" << std::endl;
}


void Document::print()
{
    std::cout << "Document {\n"
        << "name: " << _filename << "\n"
        << "}\n";
}
