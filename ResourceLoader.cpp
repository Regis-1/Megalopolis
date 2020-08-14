#include "ResourceLoader.h"

SDL_Texture* ResourceLoader::LoadTextureFromFile( const char* path )
{
    SDL_Texture* tmpTexture = IMG_LoadTexture( Renderer::Get().GetRenderer(), path );
    if( tmpTexture == nullptr )
        Logger::Get().PrintSdlImageError();

    return tmpTexture;
}

//LOADING
int** ResourceLoader::LoadMapFromFile( const char* path, int& N)
{
    int** mapMatrix = nullptr;
    int counter = 0;
    std::ifstream fs;

    fs.open(path);
    if( fs.is_open() )
    {
        fs >> N;
        mapMatrix = new int* [N];
        for( int i = 0; i < N; i++ )
            mapMatrix[i] = new int [N];

        while( !fs.eof() )
        {
            fs >> mapMatrix[counter%N][counter/N];
            counter++;
        }
        Logger::Get().PrintMessage("Loading map successful!");
    }
    else
        Logger::Get().PrintMessage("Unable to open file!");

    fs.close();

    return mapMatrix;
}

//SAVING
void ResourceLoader::SaveMapInFile( const char* path, int N, int** mapMatrix )
{
    std::ofstream fs;
    fs.open( path, std::ios::trunc );

    if( fs.is_open() )
    {
        fs << N << "\n"; //Adding map size
        for( int i=0; i<N; i++ )
            for( int j=0; j<N; j++ )  //writing mapMatrix to save file
            {
                fs << mapMatrix[j][i];
                if( j != N-1 )
                    fs << " ";
                else
                    fs << "\n";
            }
    }
    else
        Logger::Get().PrintMessage("Unable to open file!");

    fs.close();
}

//Generating Perlin noise array with variable octaves number, map size and bias
//Function returns average of Perlin's noise
float ResourceLoader::PerlinNoise2D( int mapSize, float* seedArray, int octaves, float bias, float* outputArray )
{
    for( int x = 0; x < mapSize; x++ )
        for( int y = 0; y < mapSize; y++ )
        {
            float noise = 0.0f;
            float scale = 1.0f;
            float scaleAcc = 0.0f;

            for( int o = 0; o < octaves; o++ )
            {
                int pitch = mapSize >> o;
                int sampleX1 = ( x / pitch ) * pitch; //Getting first sample for both coordinates
                int sampleY1 = ( y / pitch ) * pitch;

                int sampleX2 = ( sampleX1 + pitch ) % mapSize; //Getting second sample for both coordinates
                int sampleY2 = ( sampleY1 + pitch ) % mapSize;

                float blendX = (float)( x - sampleX1 ) / (float)pitch; //How far we are in this sampling
                float blendY = (float)( y - sampleY1 ) / (float)pitch;

                float sampleT = ( 1.0f - blendX ) * seedArray[sampleY1*mapSize + sampleX1] + blendX * seedArray[sampleY1*mapSize + sampleX2];
                float sampleB = ( 1.0f - blendX ) * seedArray[sampleY2*mapSize + sampleX1] + blendX * seedArray[sampleY2*mapSize + sampleX2];
                scaleAcc += scale;
                noise += ( blendY * (sampleB - sampleT) + sampleT ) * scale;
                scale = scale / bias; //Dividing scale by bias (the lower bias the more higher frequencies has impact)
            }
            //scale to seed range
            outputArray[y * mapSize + x] = noise / scaleAcc;
        }

    float sum = 0.0f;
    int n = mapSize * mapSize;
    for( int i = 0; i < n; i++ )
        sum += outputArray[i];

    return sum/n;
}
