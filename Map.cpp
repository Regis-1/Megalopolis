#include "Map.h"

Map::Map( int N )
    : N(N)
{
    LoadTexture( "Res/grounds.png" );
    LoadTexture( "Res/buildings.png" );

    //creating map
    idMap = new int* [N];
    for( int i=0; i<N; i++ )
    {
        idMap[i] = new int [N];
    }

    for( int i=0; i<N; i++ )
        for( int j=0; j<N; j++ )
            idMap[i][j] = 0;
}

Map::Map( const char* path )
{
    LoadTexture( "Res/grounds.png" );
    LoadTexture( "Res/buildings.png" );

    //loading map from save file
    idMap = ResourceLoader::Get().LoadMapFromFile(path, this->N);
}

Map::~Map()
{
    for( int i=0; i<(int)textures.size(); i++ )
        UnloadTexture(i);

    for( int i=0; i<(this->N); i++ )
    {
        delete [] idMap[i];
    }
    delete [] idMap;
}

void Map::LoadTexture( const char* path )
{
    SDL_Texture* tmpTex = ResourceLoader::Get().LoadTextureFromFile( path );
    this->textures.push_back( tmpTex );
    tmpTex = nullptr;
}

void Map::UnloadTexture( const int n )
{
    SDL_DestroyTexture( this->textures[n] );
    textures.erase( textures.begin() + n );
}

void Map::Save( const char* path )
{
    Logger::Get().PrintMessage("Saving...");
    ResourceLoader::Get().SaveMapInFile( path, this->N, this->idMap );
    Logger::Get().PrintMessage( "Map saved." );
}

void Map::Draw(Camera cam)
{
    SDL_Rect texRect;
    SDL_Rect drawRect;
    Vector3i tileVec;

    if( this->N == 0 )
    {
        Logger::Get().PrintMessage("Map size equals 0!");
        return;
    }

    for( int i=0; i<N; i++ )
        for( int j=0; j<N; j++ )
        {
            //Checking if tile fits in camera. If not then not render it. Simple as that
            if( i*32 - cam[0] >= 0 && i*32 - cam[0] < cam[2] && j*32 - cam[1] >= 0 && j*32 - cam[1] < cam[3] )
            {
                tileVec = this->textureTiles[this->idMap[i][j]];
                texRect = {tileVec[1]*32, tileVec[2]*32, 32, 32}; //this also has to be changed
                drawRect = {i*32 - cam[0], j*32 - cam[1], 32, 32};
                SDL_RenderCopy( Renderer::Get().GetRenderer(), (this->textures)[tileVec[0]], &texRect, &drawRect );
            }
        }
}

void Map::GenerateMap()
{
    float average;
    int maxOctave = std::log2( this->N );
    int octaves;
    float scalingBias;

    float* seedArray = new float[this->N * this->N];
    float* perlinNoiseArray = new float[this->N * this->N];

    //Randomizing generation
    for( int i = 0; i < (this->N * this->N); i++ )
        seedArray[i] = (float)rand() / (float)RAND_MAX;

    octaves = rand() % maxOctave + 1; //octaves number, from 1 to max possible
    scalingBias = ((float)rand() / (float)RAND_MAX) + 0.1f;

    //Generating an array of Perlin noise
    average = ResourceLoader::Get().PerlinNoise2D( this->N, seedArray, octaves, scalingBias, perlinNoiseArray );

    //Making simple threshold for Perlin noise [ >=average ground, <average water ]
    for( int x = 0; x < this->N; x++ )
        for( int y = 0; y < this->N; y++ )
        {
            if( perlinNoiseArray[y * this->N + x] >= average )
            {
                int randomNumber = rand() % 4;
                if( randomNumber < 3 ) //TESTING new tiles into randomizer like trees on the ground
                    this->idMap[x][y] = Tile::ground;
                else
                    this->idMap[x][y] = Tile::forest;
            }
            else
                this->idMap[x][y] = Tile::water;
        }

    delete [] seedArray;
    delete [] perlinNoiseArray;
}

//Overloading
int* Map::operator[]( unsigned int n )
{
    return (this->idMap)[n];
}
