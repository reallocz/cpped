#include "core/document.h"
#include <iostream>
#include <memory.h>

Document::Document()
{
    _filename = DDEF_FILENAME;
    _numlines = DDEF_NUMLINES;

    _lines = new Line[_numlines];
    for(unsigned int i = 0; i < _numlines; ++i)
    {
        _lines[i].setNum(i);
    }

    setCurrentLine(0);
}


Document::~Document()
{
    deleteLines();
    _log << Log::L << __func__ <<
        ":Document closed" << std::endl;
}

unsigned int Document::numlines() const
{
    return _numlines;
}


const Line& Document::operator[](unsigned int index)
{
    if(index >= _numlines)
    {
        _log << Log::E << __func__ <<
            ":OUTOFBOUND line access in document: "
            << index << "/" << _numlines << std::endl;
        throw;
    }
    else
        return _lines[index];
}


void Document::deleteLines()
{
    if(_lines == nullptr)
    {
        _log << Log::E << __func__ <<
            ":called on nullptr!" << std::endl;
    }
    else
    {
        _log << Log::L << __func__ <<
            ":Deleting lines!" << std::endl;
        delete[] _lines;
        _lines = nullptr;
    }
}


void Document::doubleLines()
{
    _log << Log::L << __func__
        << ":Doubling lines: " << _numlines << " -> " << _numlines * 2 << std::endl;

    _numlines *= 2;
    resize();
}


void Document::resize()
{
    Line* newlines = new Line[_numlines];
    if(newlines == nullptr)
    {
        std::cerr << "Error:Line : Failed to resize!" << std::endl;
    }
    memset(newlines, 0, _numlines * sizeof(_lines[0]));
    memcpy(newlines, _lines, _numlines * sizeof(_lines[0]));
    deleteLines();
    _lines = newlines;
}


Line& Document::currentLine()
{
    Line& curline = _lines[_curline];
    if(!curline.isactive())
        _log << Log::W << __func__ << ":Current line not active!" << std::endl;
    return curline;
}


void Document::setCurrentLine(unsigned int lineno)
{
    _curline = lineno;
    _lines[_curline].setactive(true);
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
        _log << Log::T << __func__ << ":Default cmd" << std::endl;
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
