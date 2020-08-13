#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <iostream>

#include "SDL2/SDL.h"

#include "Vector2i.h"

class Camera
{
private:
    int x, y;
    int w, h;
    int cameraSpeed = 32;
    int cursor_x = 0, cursor_y = 0;

public:
    Vector2i lastMoveVec = Vector2i(); //Sharing movement information to other components

    Camera() = delete;
    Camera( int x, int y, int w, int h )
        : x(x), y(y), w(w), h(h) {}

    void UpdateCursorPos( int x, int y );
    void Move( int mapSize, Vector2i &direction );

    //overloading
    int& operator[]( unsigned int n );
};

#endif // CAMERA_H_INCLUDED
