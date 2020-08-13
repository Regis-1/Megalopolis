#ifndef VECTOR2I_H_INCLUDED
#define VECTOR2I_H_INCLUDED

#include "Logger.h"

class Vector2i
{
private:
    int x, y;

public:
    Vector2i() : x(0), y(0) {}
    Vector2i( int x, int y ) : x(x), y(y) {}

    //Overloading
    int& operator[]( int n );
    Vector2i operator+( Vector2i other );
    bool operator==( Vector2i other );
    Vector2i operator-();
    Vector2i operator*( int scalar );
};

#endif // VECTOR2I_H_INCLUDED
