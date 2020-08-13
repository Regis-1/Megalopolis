#include "Map.h"

Map::Map( int N )
    : N(N)
{
    LoadTexture( "Res/grounds.png" );
    LoadTexture( "Res/buildings.png" );

    //creating map
    tileMap = new Vector3i* [N];
    for( int i=0; i<N; i++ )
    {
        tileMap[i] = new Vector3i [N];
    }
}

Map::Map( const char* path )
{
    LoadTexture( "Res/grounds.png" );
    LoadTexture( "Res/buildings.png" );

    //loading map
    tileMap = ResourceLoader::Get().LoadMapFromFile(path, this->N);
}

Map::~Map()
{
    for( int i=0; i<(int)textures.size(); i++ )
        UnloadTexture(i);

    for( int i=0; i<(this->N); i++ )
    {
        delete [] tileMap[i];
    }
    delete [] tileMap;
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

Vector2i Map::GetTilePos( int r, int c )
{
    Vector2i t_pos = Vector2i( this->tileMap[r][c][1], this->tileMap[r][c][2] );
    return t_pos;
}

int& Map::GetTileTex( int r, int c )
{
    return this->tileMap[r][c][0];
}

void Map::ChangeTile( int r, int c, Vector3i newVec )
{
    this->tileMap[r][c][0] = newVec[0];
    this->tileMap[r][c][1] = newVec[1];
    this->tileMap[r][c][2] = newVec[2];
}

void Map::Save( const char* path )
{
    Logger::Get().PrintMessage("Saving...");
    ResourceLoader::Get().SaveMapInFile( path, this->N, this->tileMap );
    Logger::Get().PrintMessage( "Map saved." );
}

void Map::Draw(Camera cam)
{
    SDL_Rect copyRect;
    SDL_Rect drawRect;
    Vector2i tilePos;

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
                tilePos = GetTilePos(i,j); //Texture tile position not the map tile position
                copyRect = {tilePos[1]*32, tilePos[0]*32, 32, 32}; //this also has to be changed
                drawRect = {i*32 - cam[0], j*32 - cam[1], 32, 32};
                SDL_RenderCopy( Renderer::Get().GetRenderer(), (this->textures)[GetTileTex(i,j)], &copyRect, &drawRect );
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
                    this->tileMap[x][y] = Vector3i(0, 0, 0);
                else
                    this->tileMap[x][y] = Vector3i(0, 1, 0);
            }
            else
                this->tileMap[x][y] = Vector3i(0, 0, 1);
        }

    delete [] seedArray;
    delete [] perlinNoiseArray;
}

//Overloading
Vector3i* Map::operator[]( unsigned int n )
{
    return (this->tileMap)[n];
}
