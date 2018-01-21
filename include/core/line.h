#pragma once
#include "core/string.h"

class Line
{
    friend class Document;

public:
    Line();
    Line(unsigned int number);
    ~Line();

    void insertChar(char a);
    void deleteChar();

    void setactive(bool value);
    bool isactive() const;
    bool isempty() const;

    unsigned int number() const;
    const char* data() const;

    unsigned int length() const;
    String slice(unsigned int from, unsigned int len) const;
    const String& getString() const;

    void print() const;

protected:
    void setNum(unsigned int num);

private:
    String _str;
    unsigned int _num;
    bool _isactive;
};
