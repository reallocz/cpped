#pragma once

#define SDEF_SIZE 8

class String
{
public:
    String();
    ~String();

    void append(char c); // Insert a char at the end

    inline unsigned int length() const { return _len; }
    unsigned int getSizeBytes() const;
    void print() const;

private:
    void doubleSize();

private:
    unsigned int _len;  // Length
    unsigned int _size; // Max length
    char* _data;
};
