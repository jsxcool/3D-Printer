#ifndef IMPROVEVERSION_STL_HH
#define IMPROVEVERSION_STL_HH

//only applicable for ASCII STL file

#include <fstream>
#include <sstream>
#include <iostream>
#include "Polyhedron.hh"

class STL{
public:
    double maxZ= -10000, minZ =10000,
            minX = 10000, minY = 10000;
    std::vector<Triangle> triangle;       // this is used for storing all the info of a STL file
public:
    void getExtremeXYZ(double x, double y, double z){
        if(z<minZ) minZ = z;
        if(z>maxZ) maxZ = z;
        if(x<minX) minX = x;
        if(y<minY) minY = y;
    }

    void load(const char filename[]) {
        std::ifstream f(filename, std::ifstream::in);
        std::string s, temp ;
        //std::string lineBuffer;
        double x, y, z;
        Vec3d v1, v2, v3;

        while( !f.eof() ) {
            f >> s;
            //could try to use getline, test speed
            if(s[0] == 'v') {
                f >> x >> y >> z;
                v1 = Vec3d(x, y, z);
                getExtremeXYZ(x, y, z);

                f>> temp >> x >> y >> z;
                v2 = Vec3d(x, y, z);
                getExtremeXYZ(x, y, z);

                f >> temp >> x >> y >> z;
                v3 = Vec3d(x, y, z);
                getExtremeXYZ(x, y, z);

                triangle.push_back(Triangle(v1, v2, v3));
            }

        }

        f.close();  //store as vector<Triangle*> triangle
    }

    //the 3D model is just positive
    void reload(){ //z must start from 0; x, y应找个适当的位置, eg: start from 0
        for(int i=0; i<triangle.size(); i++){
            triangle[i].vertex1.x -= minX;
            triangle[i].vertex1.y -= minY;
            triangle[i].vertex1.z -= minZ;

            triangle[i].vertex2.x -= minX;
            triangle[i].vertex2.y -= minY;
            triangle[i].vertex2.z -= minZ;

            triangle[i].vertex3.x -= minX;
            triangle[i].vertex3.y -= minY;
            triangle[i].vertex3.z -= minZ;
        }
        maxZ -= minZ;
        minX = 0;
        minY = 0;
        minZ = 0;
    }

    void setMinPointMove(double xDistance, double yDistance){  //最小点坐标移动到（x+xDistance，y+yDistance）
        for(int i=0; i<triangle.size(); i++){
            triangle[i].vertex1.x += xDistance;
            triangle[i].vertex1.y += yDistance;

            triangle[i].vertex2.x += xDistance;
            triangle[i].vertex2.y += yDistance;

            triangle[i].vertex3.x += xDistance;
            triangle[i].vertex3.y += yDistance;
        }

    }

    void printSTL(){
        for(int i=0; i<triangle.size(); i++)
            std::cout << triangle[i]<<'\n';
    }

};


#endif //IMPROVEVERSION_STL_HH
