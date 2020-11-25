#include <iostream>
#include <string>
#include <math.h>
using namespace std;

const double Pi = 3.141592653589793;

const int iSize = 256;

int main(int argc, char **argv)
{   
    if(argc < 2)
    {
        std::cout << "Usage : " << argv[0] << " code" << std::endl;
        return -1;
    }

    std::string value(argv[1]);

    auto x = iSize * atoi(value.substr(0,7).c_str()) + atoi(value.substr(14,3).c_str());

    auto y = iSize * atoi(value.substr(7,7).c_str()) + atoi(value.substr(17,3).c_str());

    auto lat =  (2 * atan(exp((y-536870912) / -170891318.8941079)) - Pi / 2) / (Pi / 180);

    auto lon = (x - 536870912)/2982616.177777778;
    std::cout.precision(10);
    std::cout << lon << "," << lat << std::endl;

    return 0;
}