#pragma once
#include <iostream>

class Log {
    enum class channel {
        L,
        W,
        E,
        T,
        U,
    };

public:
    Log(const char* classname);
    ~Log();

    inline const char* chname() const;
    inline std::ostream& chstream() const;

    Log& operator<<(channel ch);

    std::ostream& operator<<(const char* msg);

    template<typename Type>
    std::ostream& operator<<(Type msg);

        
public:
    const char* _classname;
    channel _channel;
    bool _fend;

    // Log channels
    static const auto L = channel::L;
    static const auto W = channel::W;
    static const auto E = channel::E;
    static const auto T = channel::T;
    static const auto U = channel::U;
};

