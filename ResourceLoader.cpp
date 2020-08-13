#include "ResourceLoader.h"

//Function for checking if texture tile from loaded file is already in std::vector of types
static int IsTileInVector( Vector3i matrixPos ,std::vector<std::vector<int>> &tTypeVec )
{
    for( int i=0; i<(int)tTypeVec.size(); i++ )
    {
        Vector3i testVec( tTypeVec[i][0], tTypeVec[i][1], tTypeVec[i][2] );
        if( testVec == matrixPos )
            return i;
    }

    return -1;
}

SDL_Texture* ResourceLoader::LoadTextureFromFile( const char* path )
{
    SDL_Texture* tmpTexture = IMG_LoadTexture( Renderer::Get().GetRenderer(), path );
    if( tmpTexture == nullptr )
        Logger::Get().PrintSdlImageError();

    return tmpTexture;
}

//LOADING
Vector3i** ResourceLoader::LoadMapFromFile( const char* path, int& N)
{
    Vector3i** mapMatrix = nullptr;
    std::ifstream fs;
    char buffer[64];
    int t_x, t_y, t_z;
    int x = 0, y = 0;
    N = 0;

    fs.open(path);
    if( fs.is_open() )
    {
        while( !fs.eof() )
        {
            fs >> buffer;
            if( strcmp( buffer, "<size>" ) == 0 )
                fs >> N;

            if( strcmp( buffer, "<tiles>") == 0 )
            {
                if( N != 0 )
                {
                    mapMatrix = new Vector3i* [N];
                    for( int i=0; i<N; i++ )
                    {
                        mapMatrix[i] = new Vector3i [N];
                    }
                }
                else
                {
                    Logger::Get().PrintMessage("Unable to load the map size!");
                    break;
                }
            }
            if( strcmp( buffer, "<textureTile>") == 0 )
            {
                fs >> t_x >> t_y >> t_z; //loading texture tile type
            }
            if( strcmp( buffer, "<positions>" ) == 0 )
            {
                fs >> x >> y; //loading tile type positions
                while( x != -1 )
                {
                    mapMatrix[x][y] = Vector3i( t_x, t_y, t_z ); //adding tile to map matrix
                    fs >> x >> y;
                }
            }
        }

        Logger::Get().PrintMessage("Loading map successful!");
    }
    else
        Logger::Get().PrintMessage("Unable to open file!");

    fs.close();

    return mapMatrix;
}

//SAVING
void ResourceLoader::SaveMapInFile( const char* path, int N, Vector3i** mapMatrix )
{
    std::ofstream fs;
    std::vector<std::vector<int>> tileTypeVectors;
    int vecSize = 0;
    const int coordsInRow = 500;
    int counter = 0;

    fs.open( path, std::ios::trunc );

    if( fs.is_open() )
    {
        fs << "<map>\n"; //Adding headers
        fs << "<size> " << N << "\n"; //Adding map size
        fs << "<tiles>\n"; //Header of the tiles section
        for( int i=0; i<N; i++)
        {
            for( int j=0; j<N; j++ )
            {
                int tileTypeIndex = IsTileInVector(mapMatrix[i][j], tileTypeVectors);
                if( tileTypeIndex == -1 )   //Adding new tile vector if this one tile was not included
                {
                    std::vector<int> t_tileVec;
                    tileTypeVectors.push_back(t_tileVec);
                    vecSize = (int)tileTypeVectors.size();
                    for( int k=0; k<3; k++ )
                        tileTypeVectors[vecSize-1].push_back(mapMatrix[i][j][k]);
                    tileTypeVectors[vecSize-1].push_back(i);
                    tileTypeVectors[vecSize-1].push_back(j);
                }
                else    //Adding only coordinates to existing vector with tileTypeIndex index
                {
                    tileTypeVectors[tileTypeIndex].push_back(i);
                    tileTypeVectors[tileTypeIndex].push_back(j);
                }
            }
        }
        vecSize = (int)tileTypeVectors.size();
        for( int i=0; i<vecSize; i++ )
        {
            auto it_beg = tileTypeVectors[i].begin();
            auto it_end = tileTypeVectors[i].begin() + 3;
            Vector3i tileVec( tileTypeVectors[i][0], tileTypeVectors[i][1], tileTypeVectors[i][2] );
            tileTypeVectors[i].erase(it_beg, it_end);
            fs << "<textureTile> " << tileVec[0] << " " << tileVec[1] << " " << tileVec[2] <<"\n";
            fs << "<positions> ";
            for( int j=0; j<(int)tileTypeVectors[i].size(); j++ )   //output all coordinates from vector
            {
                fs << tileTypeVectors[i][j] << " ";
                counter++;
                if( counter == coordsInRow )
                {
                    fs << "\n";
                    counter = 0;
                }
            }
            fs << "-1 -1\n"; //Magic coordinates to mark the end
            tileTypeVectors[i].clear(); //Clearing all vector of positions
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
