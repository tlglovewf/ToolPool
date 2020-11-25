#include <iostream>

#include "GeoHelper.h"
using namespace std;


int main(int argc, char **argv)
{
    if(argc < 4)
    {
        std::cout << "Param's Number Not Enough~" << std::endl;
        std::cout << "Usage : " << argv[0] << " x y zoom" << endl;
        return -1;
    }
        
    int x   = atoi(argv[1]);
    int y   = atoi(argv[2]);
    int zoom= atoi(argv[3]);
    
    double lon = GeoHelper::TileX2Lon(x, zoom);
    double lat = GeoHelper::TileY2Lat(y, zoom);

    std::cout << "lon and lat : " << lon << " " << lat << std::endl;
    return 0;
}