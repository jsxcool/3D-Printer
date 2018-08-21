#include <iostream>
#include "STL.hh"
#include "SliceAlgorithm.hh"
#include "FillingAlgorithm.hh"
#include "Gcode.hh"
using namespace std;

int main() {
    STL s ;
    s.load("/Users/shangxingjiang/Desktop/TestZone/children.stl");
    cout << s.minZ <<' '<< s.maxZ <<' '<<s.minX<<' '<<s.minY <<'\n';
    //s.printSTL();
    s.reload();
    cout << s.minZ <<' '<< s.maxZ <<' '<<s.minX<<' '<<s.minY <<'\n';
    //s->setMinPointMove(100, 100);

    double Zinterval = 0.2;

    Layer layer(s, 2);
    Gcode c(0.2, 6000, 900, 1800);

    layer.findIntersections();
    layer.getBoundary();
    layer.sortBoundary();
    layer.generateLines();
    //layer[i].printBoundary();
    layer.sortLines();
    /*  layer.fill(50);
      //layer[i].printFillingLines();
      c.outputGLayer(layer); */

    return 0;
}