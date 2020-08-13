#include "Camera.h"

void Camera::UpdateCursorPos( int x, int y )
{
    this->cursor_x = x;
    this->cursor_y = y;
}

void Camera::Move( int mapSize, Vector2i &direction )
{
    int prevX = this->x;
    int prevY = this->y;

    this->x += direction[0] * this->cameraSpeed;
    this->y += direction[1] * this->cameraSpeed;

    if( this->x < 0 )
        this->x = 0;
    else if( this->x + this->w > (mapSize-1)*32 )
        this->x = this->x - this->cameraSpeed;
    if( this->y < 0 )
        this->y = 0;
    else if( this->y + this->h > (mapSize-1)*32 )
        this->y = this->y - this->cameraSpeed;

    if( this->x != prevX || this->y != prevY )
        this->lastMoveVec = direction;
    else
        this->lastMoveVec = Vector2i(0, 0);
    direction = Vector2i(0, 0);
}

//Overloading
int& Camera::operator[]( unsigned int n )
{
    if( n >= 0 && n < 6)
        switch(n)
        {
        case 0:
            return this->x;
        case 1:
            return this->y;
        case 2:
            return this->w;
        case 3:
            return this->h;
        case 4:
            return this->cursor_x;
        case 5:
            return this->cursor_y;
        }
    else
        std::cout << "Invalid camera index!" << std::endl;

    return this->x;
}
