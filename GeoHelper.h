
#ifndef _GEOHELPER_H_
#define _GEOHELPER_H_
#include <algorithm>
#include <math.h>
#define M_PI 3.141592653589793238462643383279
            
/* gis相关操作
 */
class GeoHelper
{
public:
    /******************************************************/
    /*********************瓦片行列号计算*********************/
    /*****************************************************/
    //! 经度->X
    static int Lon2tileX(double lon, int zoom)
    {
        return (int)(floor((lon + 180.0) / 360.0 * pow(2.0,zoom)));
    }
    //! 维度->Y
    static int Lat2tileY(double lat, int zoom)
    {
        double radians = lat * (M_PI / 180.0);

        return (int)(floor((1.0 - (log(tan(radians) + 1.0 / cos(radians)) / M_PI)) * pow(2.0, zoom - 1)));
    }
    //! X->经度
    static double TileX2Lon(int tileX, int zoom)
    {
        return tileX / pow(2.0, zoom) * 360.0 - 180.0;
    }
    //! Y->维度
    static double TileY2Lat(int tileY, int zoom)
    {
        double n = M_PI - 2.0 * M_PI * tileY / pow(2.0, zoom);
        return 180.0 / M_PI * atan(0.5 * (exp(n) - exp(-n)));
    }
    //! 行列号有效性判断
    static bool IsTileXYValid(int x, int y, int zoom)
    {
        int tilecount = GetTileXYCount(zoom);

        if( x < 0 || y < 0 || x >= tilecount || y >= tilecount)
            return false;
        else
            return true;
    }

    //! 取摩卡托层级下瓦片总数
    static int GetTileXYCount(int zoom)
    {
        return pow(2.0, zoom);
    }
};




#endif