#ifndef IMPROVEVERSION_GCODE_HH
#define IMPROVEVERSION_GCODE_HH

#include "SliceAlgorithm.hh"

class Gcode{
private:
    std::ofstream f;  // used to output to a target file

    double E = 0.08;  // initialize
    double Einterval;   // 每次喷出的量

    double F0;    // speed(uncontrolled) = mm/min
    double F1B;    // for boundary
    double F1F;   // for fill

    void G0Z(double F, double z){
        f << "G0 F"<< F << " Z" << z <<'\n';
    }

    void G0(double F, double x, double y){
        f << "G0 F"<< F <<" X" << x << " Y" << y <<'\n';
    }

    void G1(double F, double x, double y, double e){
        f << "G1 F"<< F <<" X" << x << " Y" << y <<" E"<< e << '\n';
    }

    void assignXYZ(double& x, double& y, Vec2d v){
        x = v.x;
        y = v.y;
    }

public:
    Gcode(double Einterval, double F0, double F1B, double F1F):
            Einterval(Einterval), F0(F0), F1B(F1B), F1F(F1F) {
        f.open("/Users/shangxingjiang/Desktop/TestZone/myGcode.gcode");
    }

    ~Gcode() { f.close(); }

    void outputGBoundary(const Layer& l){    // for boundary
        for(int i=0; i<l.boundary.size(); i++) {
            Vec2d* v=l.boundary[i].head;
            double x = v->x;
            double y = v->y;
            G0(F0, x, y);
            for (; v != nullptr; v = v->next, E += Einterval) {
                assignXYZ(x, y, *v);
                G1(F1B, x, y, E);
            }
            //indent(b.boundary[i]);  //缩进后，是否让它成为新的边界??
        }
    }

    void outputGFill(const Layer& l){
        Vec2d v ;
        double x=0, y=0, z=0;
        int index = 0;
        for(int i=0; i<l.inter.size(); i++) {
            //此if可能存在问题：最后一次x，我们不知道有几个填充线  !!!!
            if (i >= l.inter.size()-1 || l.inter[i].position1.x != l.inter[i+1].position1.x ) {
                v = l.inter[i].position1;
                if (i % 2 == 1)
                    v = l.inter[i].position2;
                assignXYZ(x, y, v);
                E += Einterval;
                G0(F0, x, y);
                G1(F1F, x, y, E);
                v = l.inter[i].position2;
                if (i % 2 == 1)
                    v = l.inter[i].position1;
                assignXYZ(x, y, v);
                E += Einterval;
                G1(F1F, x, y, E);
            }
            else{
                double tempX = l.inter[i].position1.x;
                if(index%2 == 0) {
                    while (tempX == l.inter[i].position1.x && i<l.inter.size()-1 ) {     // stuck here：i = b.inter.size()   34--38
                        v = l.inter[i].position1;
                        assignXYZ(x, y, v);
                        E += Einterval;
                        G0(F0, x, y);
                        G1(F1F, x, y, E);
                        v = l.inter[i].position2;
                        assignXYZ(x, y, v);
                        E += Einterval;
                        G1(F1F, x, y, E);
                        i++;
                    }
                    index++;
                }
                else{
                    int startNum = i;
                    while (tempX == l.inter[i].position1.x && i<l.inter.size()-1 )     //stuck here
                        i++;
                    for(int j=i-1; j>= startNum; j--){
                        v = l.inter[j].position2;
                        assignXYZ(x, y, v);
                        E += Einterval;
                        G0(F0, x, y);
                        G1(F1F, x, y, E);
                        v = l.inter[j].position1;
                        assignXYZ(x, y, v);
                        E += Einterval;
                        G1(F1F, x, y, E);
                    }
                    index++;
                }
                i--;  //因为最后一次内部循环已经导致i多加了1
            }

        }
    }

    void outputGLayer(const Layer& l) {
        G0Z(F0, l.getZ());
        outputGBoundary(l);
        outputGFill(l);
    }


};




#endif //IMPROVEVERSION_GCODE_HH
