#pragma once

class Doccmd
{
public:
    // Command structs
    struct Insertchar {
        char c;
    };
    
    struct Move {
        enum Type {
            right,
            left,
            down,
            up
        };

        Type type;
        int count;
    };

    struct Edit {
        enum Type {
            deletechar,
            newline,
        };
        Type type;
    };

    struct Save {
        bool saveas;
    };


public:
    enum class Type {
        Insertchar,
        Edit,
        Move,
        Save,
    };

    union Command {
        Insertchar insertchar;
        Edit edit;
        Move move;
        Save save;
    };
public:
    Type type;
    Command cmd;
};
