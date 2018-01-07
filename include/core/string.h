#pragma once

#define SDEF_SIZE 8

class String
{
public:
    String();
    String(const char* str);
    ~String();

    void append(char c); // Insert a char at the end

    inline unsigned int length() const { return _len; }
    unsigned int getSizeBytes() const;
    unsigned int getLengthBytes() const;
    void print() const;

    char operator[](unsigned int pos) const;
    void operator=(const char* str);

private:
    void doubleSize();

private:
    unsigned int _len;  // Length
    unsigned int _size; // Max length
    char* _data;
};
