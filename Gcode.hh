//transfer coordinates(Vec3d) to Gcode
//G0:表示喷头前进到的位置     //G1：喷头的工作路线
#ifndef INPUT_CLASS_GCODE_HH
#define INPUT_CLASS_GCODE_HH

#include "SliceAlgorithm.hh"

class Gcode{
public:
    static void outputGcode(const Boundary& b){
        std::ofstream f;
        f.open("myGcode");
        Vec3d* v=b.head;
        double x = v->x;
        double y = v->y;
        double z = v->z;
        f << "G0 X" << x << " Y" << y << " Z"<< z <<'\n';
        for( ; v != nullptr; v = v->next ){
            x = v->x;
            y = v->y;
            z = v->z;
            f << "G1 X" << x << " Y" << y << " Z"<< z <<'\n';
        }
        f.close();
    }
};


#endif
