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
    void print() const;
    std::vector<std::string> lines() { return _lines; };

    friend std::ostream& operator<<(std::ostream& o, const Document& d);


private:
    std::string _filename;
    std::vector<std::string> _lines;   // Lines
    unsigned int _curline;  // Cursor line
    unsigned int _curcol;   // Curosor column
};
