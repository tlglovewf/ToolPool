#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

struct Vec3d
{
    double _x;
    double _y;
    double _z;
    Vec3d():_x(0),_y(0),_z(0){}
    Vec3d(double a, double b, double c):_x(a),_y(b),_z(c){}
    void normalize()
    {
       double d = sqrtf(_x * _x + _y * _y + _z * _z);
       _x /= d;
       _y /= d;
       _z /= d;
    }
    double& x(){return _x;}
    double& y(){return _y;}
    double& z(){return _z;}

    double x()const{return _x;}
    double y()const{return _y;}
    double z()const{return _z;}
};

Vec3d operator-( Vec3d &lhs,  Vec3d &rhs)
{
  return Vec3d(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
}

bool operator==(const Vec3d &lhs,const Vec3d &rhs)
{
  return (lhs.x()  == rhs.y()) &&
         (lhs.y()  == rhs.y()) &&
         (lhs.z() == rhs.z());
}

Vec3d operator^(const Vec3d &lhs, const Vec3d &rhs)
{
  return Vec3d(lhs.x()*rhs.y()-lhs.y()*rhs.x(),
               lhs.z()*rhs.x()-lhs.x()*rhs.z() ,
               lhs.x()*rhs.y()-lhs.y()*rhs.x());
}


typedef std::vector<Vec3d> Vecs;


enum OrientType
{
  ORIENTATION_CW  ,
  ORIENTATION_CCW ,
  NONTYPE
};

static inline  int64_t det(const Vec3d &a, const Vec3d &b)  {
       return static_cast<int64_t>(a.x()) * static_cast<int64_t>(b.y()) -
              static_cast<int64_t>(b.x()) * static_cast<int64_t>(a.y());
   }



OrientType GetOrientation2(const Vecs &items)
{
  int64_t sum = 0;
  if(items.empty())
    return OrientType::NONTYPE;
  Vec3d last_point  = items[0];
  Vec3d start_point = items[0];
   for(size_t i = 1; i < items.size(); ++i)
   {
      sum += det(last_point, items[i]);
      last_point = items[i];
   }

    //  E|XnYn+1 - YnXn+1|  check if clockwise
    sum += det(last_point, start_point);

   return (sum > 0 ? ORIENTATION_CCW :
           sum < 0 ? ORIENTATION_CW : NONTYPE);
}

OrientType GetOrientation(const Vecs &items) 
{
    // adjust for a non-open ring:
    int n = items.size();
    if ( n > 0 && *items.begin() == *items.rbegin() )
        n--;

    if ( n < 3 )
        return NONTYPE;

    // copy the open vec:
    Vecs v;
    v.reserve( n );
    std::copy( items.begin(), items.begin()+n, std::back_inserter(v) );

    int rmin = 0;
    double xmin = v[0].x();
    double ymin = v[0].y();
    v[0].z() = 0;
    for( int i=1; i<n; ++i ) {
        double x = v[i].x();
        double y = v[i].y();
        v[i].z() = 0;
        if ( y > ymin )
            continue;
        if ( y == ymin ) {
            if (x  < xmin )
                continue;
        }
        rmin = i;
        xmin = x;
        ymin = y;
    }

    int rmin_less_1 = rmin-1 >= 0 ? rmin-1 : n-1;
    int rmin_plus_1 = rmin+1 < n ? rmin+1 : 0;

    Vec3d in = v[rmin] - v[rmin_less_1]; 
    in.normalize();
    Vec3d out = v[rmin_plus_1] - v[rmin]; 
    out.normalize();
    Vec3d cross = in ^ out;
    return
        cross.z() < 0.0 ? ORIENTATION_CW :
        cross.z() > 0.0 ? ORIENTATION_CCW :
        NONTYPE;
}

void displayType(OrientType type)
{
    switch (type)
    {
    case ORIENTATION_CW:
      std::cout << "clock wise" ;
      break;
    case ORIENTATION_CCW:
      std::cout << "counter clock wise" ;
      break;
    default:
      std::cout << "none type." ;
      break;
    }
}

void DisplayFromFile(const std::string &path)
{
  ifstream ifile(path);
  if(ifile.is_open())
  {
      while(!ifile.eof())
      {
         std::string line;
         getline(ifile,line);
         if(!line.empty())
         {
            Vecs ves;
            size_t pos = 0;
            size_t st_i = line.find_first_of('(');
            size_t ed_i = line.find_first_of(')');
            ++st_i;
            line = line.substr(st_i,ed_i - st_i);
            while(pos != string::npos)
            {
              int x,y;
              pos = line.find_first_of(',');
              sscanf(line.substr(0,pos).c_str(),"%d %d",&x,&y);
              ves.emplace_back(Vec3d(x,y,0));
              line = line.substr(pos + 1);
            }
            static int linIdx = 1;
            std::cout << "Line " << linIdx++ << " result : " ;
            std::cout << "Func 1 " ; displayType(GetOrientation(ves)) ;
            std::cout << "||Func 2 "; displayType(GetOrientation2(ves));
            std::cout << std::endl;
         }
      }
  }
  else
  {
    throw "error";
  }
}

int main(int argc, char **argv)
{
  if(argc < 2)
  {
     std::cout << "Usage " << argv[0] << " filepath" << " juge func type (0|1)" << std::endl;
     return -1;
  }

  std::cout << "read file " << argv[1] << std::endl;

  DisplayFromFile(argv[1]);

  return 0;
}
