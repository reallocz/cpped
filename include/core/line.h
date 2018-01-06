#pragma once

#define LDEFAULT_SIZE 8

class Line
{
public:
    Line();
    ~Line();
    void insert(char c); // Insert a char at the cur pos
    void print() const;

private:
    void doubleSize();

private:
    unsigned int _len;  // Length
    unsigned int _cur;  // Cursor position
    unsigned int _size; // Max length
    char* _data;
};
