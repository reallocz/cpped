#include "log.h"

Log::Log(const char* classname)
{
    _classname = classname;  
    _channel = channel::L;
}


Log::~Log()
{}


Log& Log::operator<<(channel ch)
{
    _channel = ch;
    chstream() << chname() << '[' << _classname << "] ";
    return *this;
}


std::ostream& Log::operator<<(const char* msg)
{
    return chstream() << msg;
}


template<typename Type>
std::ostream& Log::operator<<(Type msg)
{
    return chstream() << msg;
}


inline const char* Log::chname() const
{
    switch(_channel)
    {
        case(L):
            return "[Log]";
        case(W):
            return "[Warn]";
        case(E):
            return "[Error]";
        case(T):
            return "[TODO]";
        default:
            return "[Unknown]";
    }
}


inline std::ostream& Log::chstream() const
{
    switch(_channel)
    {
        case(L):
            return std::cout;
        case(W):
            return std::cout;
        case(E):
            return std::cerr;
        case(T):
            return std::cout;
        default:
            return std::cerr;
    }
}
