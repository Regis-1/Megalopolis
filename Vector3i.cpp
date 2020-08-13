#include "Vector3i.h"

int& Vector3i::GetX()
{
    return this->x;
}

int& Vector3i::GetY()
{
    return this->y;
}

int& Vector3i::GetZ()
{
    return this->z;
}

//Overloading
int& Vector3i::operator[]( unsigned int n )
{
    switch(n)
    {
    case 0:
        return this->x;
    case 1:
        return this->y;
    case 2:
        return this->z;
    default:
        Logger::Get().PrintMessage("Wrong Vector3i index!");
    }
    return this->x;
}

bool Vector3i::operator==( Vector3i other )
{
    if( this->x == other[0] )
        if( this->y == other[1] )
            if( this->z == other[2] )
                return true;
            else
                return false;
        else
            return false;
    else
        return false;
}

std::ostream& operator<<( std::ostream& out, Vector3i vec )
{
    out << "Vector: x=" << vec.GetX() << " y=" << vec.GetY() << " z=" << vec.GetZ();
    return out;
}
