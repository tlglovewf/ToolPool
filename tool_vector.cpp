#include "clara.hpp"
#include <string>
#include <iostream>
int main(int argc, char **argv)
{
   std::string filename; 
   bool bol = false;
   bool help = false;
   const auto cli = clara::Opt(bol)["-a"]["--all"]("show all files")|
	   				clara::Help(help)|
	   				clara::Arg(filename,"FileName").required();
   const auto result = cli.parse(clara::Args(argc,argv));
   if(!result)
   {
	   	std::cerr << "error in command line : " << result.errorMessage() << std::endl;
	   return -1;
   }
   if(help){std::cout << cli << std::endl;}
   if(filename.empty()){std::cout<<"file empty!!!" << std::endl;return -1;}
   return 0;
}
