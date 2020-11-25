#include <iostream>

#include "GeoHelper.h"
using namespace std;


int main(int argc, char **argv)
{
    if(argc < 4)
    {
        std::cout << "Param's Number Not Enough~" << std::endl;
        std::cout << "Usage : " << argv[0] << " lon lat zoom" << endl;
        return -1;
    }
        
    double lon = atof(argv[1]);
    double lat = atof(argv[2]);
    int    zoom= atoi(argv[3]);
    int x = GeoHelper::Lon2tileX(lon,zoom);
    int y = GeoHelper::Lat2tileY(lat,zoom);
    std::cout << "X and Y : " << x << " " << y << std::endl;
    return 0;
}