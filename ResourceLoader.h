#ifndef RESOURCELOADER_H_INCLUDED
#define RESOURCELOADER_H_INCLUDED

#include <fstream>
#include <cstring>
#include <vector>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Logger.h"
#include "Renderer.h"
#include "Vector3i.h"
#include "stdlib.h"
#include "time.h"

class ResourceLoader
{
private:
    ResourceLoader() {}
    ResourceLoader( const ResourceLoader& ) {}
    ~ResourceLoader() {};
public:
    static ResourceLoader& Get()
    {
        static ResourceLoader instance;
        return instance;
    }

    //Methods
    SDL_Texture* LoadTextureFromFile( const char* path );
    Vector3i** LoadMapFromFile( const char* path, int& N );
    void SaveMapInFile( const char* path, int N, Vector3i** mapMatrix );
    float PerlinNoise2D( int mapSize, float* seedArray, int octaves, float bias, float* outputArray );
};

#endif // RESOURCELOADER_H_INCLUDED
