#pragma once
#include <string>
#include <vector>

class Document {
public:
    Document();
    virtual ~Document();
    void insert(char c);
    void moveRight();
    void moveLeft();
    void log() const;
    void print() const;

private:
    std::string _filename;
    std::vector<std::string> _lines;   // Lines
    unsigned int _curline;  // Cursor line
    unsigned int _curcol;   // Curosor column
};
