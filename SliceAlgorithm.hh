#ifndef IMPROVEVERSION_SLICEALGORITHM_HH
#define IMPROVEVERSION_SLICEALGORITHM_HH

#include "STL.hh"
#include <cmath>
#define threForSame 0.0000001

class Layer{
private:
    STL myFile;
    double z;  // scanning line height
    std::vector<Intersection> intersection;  // two intersections (Vec2d) with two sides of a triangle

    std::vector<Line> line;          // convert the boundary to many lines
public:
    std::vector<Linkedlist> boundary;
    std::vector<Intersection> inter; // 与边界上两条边的两个交点
public:
    Layer(STL s, double z): myFile(s), z(z) {}

    double getZ() const { return z;}

    // knowing two vertexes of one side and height z, calculate the intersection coordinate
    Vec2d pointAsZ(Vec3d v1, Vec3d v2){   //知道某条线与切割线（切三角形）交点的z坐标，求交点的坐标
        double x1 = v1.x, y1= v1.y, z1 = v1.z;
        double x2 = v2.x, y2= v2.y, z2 = v2.z;
        return Vec2d((x1 - x2)*(z - z1) / (z1 - z2) + x1, (y1 - y2)*(z - z1) / (z1 - z2) + y1);
    }

    bool crossEdge(Vec3d v1, Vec3d v2){   //scanning line crosses an edge of a triangle
        if( std::min(v1.z, v2.z)< z && z < std::max(v1.z, v2.z) )
            return true;
        return false;
    }

    void findIntersections(){
        for(int i=0; i<myFile.triangle.size(); i++){
            Triangle tri = myFile.triangle[i];
            Vec2d p1,  p2 ;

            if(crossEdge(tri.vertex1, tri.vertex2) && crossEdge(tri.vertex1, tri.vertex3)){
                p1 = pointAsZ(tri.vertex1, tri.vertex2);
                p2 = pointAsZ(tri.vertex1, tri.vertex3);
            }

            if(crossEdge(tri.vertex1, tri.vertex2) && crossEdge(tri.vertex2, tri.vertex3)){
                p1 = pointAsZ(tri.vertex1, tri.vertex2);
                p2 = pointAsZ(tri.vertex2, tri.vertex3);
            }

            if(crossEdge(tri.vertex1, tri.vertex3) && crossEdge(tri.vertex2, tri.vertex3)){
                p1 = pointAsZ(tri.vertex1, tri.vertex3);
                p2 = pointAsZ(tri.vertex2, tri.vertex3);
            }

            if( z==tri.vertex1.z  || z==tri.vertex2.z  || z==tri.vertex3.z ){
                // the whole triangle is on the z cross layer
                if(tri.vertex1.z==tri.vertex2.z && tri.vertex1.z==tri.vertex3.z)  //如果三角形三点都在此Z平面上，略过
                    continue;

              // one side is on the cross layer
                if (z==tri.vertex1.z && z==tri.vertex2.z && z<tri.vertex3.z ){  //可能导致重复添加intersection
                    p1 = tri.vertex1.toVec2d();                                 // 故加了第三个 && 条件
                    p2 = tri.vertex2.toVec2d();
                }
                else if (z==tri.vertex1.z && z==tri.vertex3.z && z<tri.vertex2.z){  //可能导致重复添加intersection
                    p1 = tri.vertex1.toVec2d();
                    p2 = tri.vertex3.toVec2d();
                }
                else if (z==tri.vertex2.z && z==tri.vertex3.z && z<tri.vertex1.z){  //可能导致重复添加intersection
                    p1 = tri.vertex2.toVec2d();
                    p2 = tri.vertex3.toVec2d();
                }

              // one vertex is on the cross layer
                if( z==tri.vertex1.z && crossEdge(tri.vertex2, tri.vertex3)){
                    p1 = tri.vertex1.toVec2d();
                    p2 = pointAsZ(tri.vertex2, tri.vertex3);
                }
                else if( z==tri.vertex2.z && crossEdge(tri.vertex1, tri.vertex3)){
                    p1 = tri.vertex2.toVec2d();
                    p2 = pointAsZ(tri.vertex1, tri.vertex3);
                }
                else if( z==tri.vertex3.z && crossEdge(tri.vertex1, tri.vertex2)){
                    p1 = tri.vertex3.toVec2d();
                    p2 = pointAsZ(tri.vertex1, tri.vertex2);
                }
            }

            if( p1.x !=-100 && p2.x !=-100 && p1 != p2)   // p1, p2 != initial value
                intersection.push_back(Intersection(p1, p2));
        }

    }

    void printIntersection(){
        for(int i=0; i<intersection.size(); i++)
            std::cout << intersection[i] <<'\n';
    }

    bool samePoint(Vec2d v1, Vec2d v2){
        if(abs(v1.x - v2.x) < threForSame && abs(v1.y - v2.y) < threForSame)
            return 1;
        return 0;
    }


    Linkedlist drawOneLinkedlist(){
        Linkedlist oneList;
        Vec2d temp;
        int index = 0;
        std::vector<int> eraseIndex;  // used to store the index
        oneList.addEnd(intersection[0].position1);
        oneList.addEnd(intersection[0].position2);
        temp = intersection[0].position2;    // 用于当作临时的最后一个节点
        eraseIndex.push_back(0);

        for(int j=1; j<intersection.size(); j++) {
            for (int i = 1; i < intersection.size(); i++) {
                if (i != index) {
                    //进度必须很小，否则可能出问题
                    // step must be small, otherwise may cause error
                    if (samePoint(intersection[i].position1, temp) ||
                            samePoint(intersection[i].position2, temp)) {
                        index = i;
                        if (samePoint(intersection[i].position1, temp)) {
                            temp = intersection[i].position2;     //如交点1和temp相等就选另一个
                            eraseIndex.push_back(i);
                        }
                        else {
                            temp = intersection[i].position1;
                            eraseIndex.push_back(i);
                        }

                        if (samePoint(temp, *oneList.head))
                            temp.completed = 1;

                        oneList.addEnd(temp);
                        break;
                    }
                }
            }

            if(temp.completed == 1) {
              // optimize: if three nodes are on the same line, delete the inner node
                oneList.optimize();   // 优化：若三点共线，只取起止点
                oneList.optimize();
                oneList.optimize();  //3次optimize, 尽量减少LinkedList上点的数量, i.e. decrease the number of line

                for(int i=0; i<eraseIndex.size()-1;i++) {      // index bubble sorting from least to biggest
                    for (int j = 0; j < eraseIndex.size() - 1; j++) {
                        int t;
                        if (eraseIndex[j] > eraseIndex[j + 1]) {
                            t = eraseIndex[j];
                            eraseIndex[j] = eraseIndex[j + 1];
                            eraseIndex[j + 1] = t;
                        }
                    }
                }

                // 问题：erase删了之后，vector<intersection*>的整个顺序立马全部变化, 故要自己设计erase的算法
                // ***follow up: we could choose set<intersection>, erase is only O(1)
                for(int i=0; i<eraseIndex.size(); i++){
                    intersection.erase(intersection.begin()+eraseIndex[i]);
                    for(int i=0; i<eraseIndex.size();i++)
                        eraseIndex[i] -= 1;
                }
                return oneList;   //优化后的boundary(Linkedlist)
            }

        }

    }

    void getBoundary(){
        while( !intersection.empty() )
            boundary.push_back(drawOneLinkedlist());
    }

    void sortBoundary(){
        Vec2d* v = new Vec2d(0, 0);
        Linkedlist temp;
        double distance = Vec2d::distance(v, boundary[0].head);
        for(int i=0; i<boundary.size(); i++){
            distance = Vec2d::distance(v, boundary[i].head);
            for(int j=i+1; j<boundary.size(); j++){
                if( Vec2d::distance(v, boundary[j].head) < distance ){
                    distance = Vec2d::distance(v, boundary[j].head);
                    temp = boundary[i];
                    boundary[i] = boundary[j];
                    boundary[j] = temp;
                }
            }
            v = boundary[i].head;
        }
    }

    void printBoundary(){
        for(int i=0; i<boundary.size(); i++)
            std::cout << boundary[i]<<'\n';
    }


    void generateLines();
    void printLines();
    void sortLines();
    void getMaxMinOfBoundary(double& maxX, double& minX, std::vector<double>& boundaryPoint);
    void fill(int n);
    void printFillingLines();

};



#endif //IMPROVEVERSION_SLICEALGORITHM_HH
