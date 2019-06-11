#ifndef IMPROVEVERSION_POLYHEDRON_HH
#define IMPROVEVERSION_POLYHEDRON_HH

#include <iostream>
#include <cmath>
#include <vector>
#define threForSame2 0.00000000001

class Vec2d{
public:
    bool completed;
    Vec2d* next;
    double x, y;
public:
    Vec2d(double x= -100, double y= -100): x(x), y(y), completed(0), next(nullptr) {}  //给这个初值是为了检测

    friend std::ostream& operator << (std::ostream& s, const Vec2d& v){
        return s <<'(' <<v.x <<' '<<v.y<<')';
    }

    bool operator ==(Vec2d right) const{
        if(x==right.x && y==right.y)
            return 1;
        else
            return 0;
    }

    bool operator !=(Vec2d right) const{
        if(abs(x-right.x)<threForSame2 && abs(y-right.y)<threForSame2 )
            return 0;
        else
            return 1;
    }

    // static: we can call this function without initializing a object
    double static distance(Vec2d* v1, Vec2d* v2){
        return sqrt((v1->x - v2->x)*(v1->x - v2->x) + (v1->y - v2->y)*(v1->y - v2->y));
    }

};

class Vec3d {  //just for storing vertexes of triangle
public:
    double x, y, z;
public:
    Vec3d(double x=0, double y=0, double z=0): x(x), y(y), z(z) {}

    Vec2d toVec2d(){
        return Vec2d(x, y);
    }

    friend std::ostream& operator << (std::ostream& s, const Vec3d& v){
        return s <<'(' <<v.x <<' '<<v.y<<' '<<v.z<<')';
    }

};

// Triangle is the basic unit for STL file encoding
class Triangle{
public:
    Vec3d vertex1;
    Vec3d vertex2;
    Vec3d vertex3;

    Triangle(Vec3d v1, Vec3d v2, Vec3d v3):
            vertex1(v1), vertex2(v2), vertex3(v3) {}

    friend std::ostream& operator << (std::ostream& s, const Triangle& t){
        return s << t.vertex1 << t.vertex2 << t.vertex3 ;
    }
};




class Intersection{
public:
    Vec2d position1, position2;

    Intersection(Vec2d p1, Vec2d p2): position1(p1), position2(p2) {}

    friend std::ostream& operator << (std::ostream& s, const Intersection& i){
        return s << i.position1 << "--" << i.position2;
    }

};

class Linkedlist{
public:
    Vec2d* head;
public:
    Linkedlist(): head(nullptr) {}

    void addEnd(Vec2d v){
        static Vec2d* temp;
        if(head == nullptr){
            head = new Vec2d();
            *head = v;
            head->next = nullptr;
            temp = head;
        }
        else{
            temp->next = new Vec2d();
            temp = temp->next;
            *temp = v;
            temp->next = nullptr;
        }
    }

    //delete the middle point in one line. (the line is on one layer)
    void optimize(){
        Vec2d* start = head;
        for(; start->next != nullptr; start = start->next){
            Vec2d* next1 = start->next;
            Vec2d* next2 = next1->next;
            if(next2 == nullptr)
                break;
            // three points on the same line
            if(abs(Vec2d::distance(start, next2) - Vec2d::distance(start, next1) -
                   Vec2d::distance(next1, next2)) < 0.001) {
                start->next = next2;
                delete next1;
            }
        }

        // the last point, head, head->next are one the same line
        if(abs(Vec2d::distance(start, head->next) - Vec2d::distance(start, head) -
               Vec2d::distance(head, head->next)) < 0.001){
            Vec2d* temp = head;
            head = head->next;
            delete temp;
            start->next = new Vec2d();
            start= start->next;
            *start = *head;
            start->next = nullptr;
        }
    }

    void getMaxMinX(double& maxX, double& minX){
        minX=10000; maxX=-10000;
        Vec2d* v = head;
        while(v != nullptr){
            if(v->x < minX)
                minX = v->x;
            if(v->x > maxX)
                maxX = v->x;
            v = v->next;
        }
    }

    friend std::ostream& operator << (std::ostream& s, const Linkedlist& l){
        Vec2d* v = l.head;
        while(v != nullptr){
            s << *v << "--";
            v = v->next;
        }
        return s;
    }

};

class Line{
public:
    Vec2d lineHead, lineTail;
public:
    Line(Vec2d v1, Vec2d v2): lineHead(v1), lineTail(v2) {}

    friend std::ostream& operator << (std::ostream& s, const Line& l){
        return s << l.lineHead << "--" << l.lineTail;
    }

    bool intersectLine(double x){
        if(x < std::min(lineHead.x, lineTail.x) || x > std::max(lineHead.x, lineTail.x) ||
           (lineHead.x == lineTail.x) )
            return 0;
        return 1;
    }

    double getY(double x){
        Vec2d min, max;
        if(lineHead.x < lineTail.x){
            min = lineHead;
            max = lineTail;
        }
        else{
            min = lineTail;
            max = lineHead;
        }

        if(min.y >= max.y)
            return max.y + (max.x - x)/(max.x - min.x)*(min.y - max.y);
        else
            return min.y + (x - min.x)/(max.x - min.x)*(max.y - min.y);
    }

};


#endif //IMPROVEVERSION_POLYHEDRON_HH
