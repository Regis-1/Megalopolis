#include "Vector2i.h"

//overloading
int& Vector2i::operator[]( int n )
{
    switch(n)
    {
    case 0:
        return this->x;
    case 1:
        return this->y;
    default:
        Logger::Get().PrintMessage("Invalid Vector2i index!");
    }

    return this->x;
}

Vector2i Vector2i::operator+( Vector2i other )
{
    Vector2i result;
    result[0] = this->x + other[0];
    result[1] = this->y + other[1];

    return result;
}

bool Vector2i::operator==( Vector2i other )
{
    if( this->x == other[0] && this->y == other[1] )
        return true;
    return false;
}

Vector2i Vector2i::operator-()
{
    Vector2i negVec;
    negVec[0] = -this->x;
    negVec[1] = -this->y;

    return negVec;
}

Vector2i Vector2i::operator*( int scalar )
{
    Vector2i result;
    result[0] = this->x*scalar;
    result[1] = this->y*scalar;

    return result;
}
