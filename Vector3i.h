#ifndef VECTOR3I_H_INCLUDED
#define VECTOR3I_H_INCLUDED

#include <cmath>
#include <iostream>

#include "Logger.h"

//Vector of three integers
class Vector3i
{
private:
    int x = 0;
    int y = 0;
    int z = 0;
public:
    Vector3i() {}
    Vector3i( int x, int y, int z )
        : x(x), y(y), z(z) {}
    ~Vector3i() {}

    //Methods
    int& GetX();
    int& GetY();
    int& GetZ();

    //Overloading
    int& operator[]( unsigned int n );
    bool operator==( Vector3i other );

};

std::ostream& operator<<( std::ostream& out, Vector3i vec );

#endif // VECTOR3I_H_INCLUDED
