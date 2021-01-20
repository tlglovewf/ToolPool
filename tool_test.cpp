#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char **argv)
{
    
    std::vector<int> ves = {10,9,19,12,3,2,1};

    std::for_each(ves.begin(), ves.end(), [](int i)->void
    {
        std::cout << i << " " << std::endl;
    });

    std::reverse(ves.begin(),ves.end());
    std::cout << "--------------" << std::endl;
    std::for_each(ves.begin(), ves.end(), [](int i)->void
    {
        std::cout << i << " " << std::endl;
    });
    return 0;
}