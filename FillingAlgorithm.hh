#include "SliceAlgorithm.hh"

#ifndef IMPROVEVERSION_FILLINGALGORITHM_HH
#define IMPROVEVERSION_FILLINGALGORITHM_HH

#include "SliceAlgorithm.hh"
//the member we need to use：vector<Linkedlist> boundary
//std::vector<Line*> line;          //convert the boundary to many lines
//std::vector<Intersection*> inter; //与边界上两条边的两个交点


void Layer::generateLines(){  // 直接对boundary操作
    for(int i=0; i<boundary.size(); i++){
        Linkedlist l = boundary[i];
        Vec2d* v = boundary[i].head;
        for(; v->next != nullptr; v = v->next )
            line.push_back(Line(*v, *v->next));
    }
}

//排序line：（1）line按y ascending排；（2）相同y，按x ascending排；（line中的两个点取那个最小的点）
bool sortRule(Line l1, Line l2){
    if(std::min(l1.lineHead.y, l1.lineTail.y) < std::min(l2.lineHead.y, l2.lineTail.y))
        return 1;
    if(std::min(l1.lineHead.y, l1.lineTail.y) == std::min(l2.lineHead.y, l2.lineTail.y)){
        if(l1.lineHead.x + l1.lineTail.x < l2.lineHead.x + l2.lineTail.x)
            return 1;
    }
    return 0;
}

void Layer::sortLines(){
    std::sort(line.begin(), line.end(), sortRule);
}

void Layer::printLines(){
    for(int i=0; i<line.size(); i++)
        std::cout << line[i] <<'\n';
}

void Layer::getMaxMinOfBoundary(double& maxX, double& minX, std::vector<double>& boundaryPoint){
    boundary[0].getMaxMinX(maxX, minX); //variable reference function(&): get min, max in the first Linkedlist;
    boundaryPoint.push_back(maxX);
    boundaryPoint.push_back(minX);
    for(int i=1; i<boundary.size(); i++) {
        double tempMax, tempMin;
        boundary[i].getMaxMinX(tempMax, tempMin);
        boundaryPoint.push_back(tempMax);
        boundaryPoint.push_back(tempMin);
        if(tempMax > maxX )
            maxX = tempMax;
        if(tempMin < minX )
            minX = tempMin;
    }
    // delete duplicate elements in vector  必要性不大
}

bool isSubset(double x, std::vector<double> a){
    for(int i=0; i< a.size(); i++)
        if(x == a[i])
            return 1;
    return 0;
}

void Layer::fill(int n) { // decide the density of filling
    double maxX, minX;
    double interval = (maxX - minX)/n;    //更合理
    if(interval < 0.2)
        interval = 0.2;    // set minimum interval = 0.2

    std::vector<double> boundaryPoint;
    getMaxMinOfBoundary(maxX, minX, boundaryPoint);

    Vec2d v1, v2;
    double y1, y2, z;
    for( double x= minX+interval; x<maxX; x += interval ){
        for(int i=0; i<line.size(); i++){

            //这两个continue有点过分，应该只跳过此条边界，而不是整个x
            if(isSubset(x, boundaryPoint))
                continue;
            if(line[i].lineHead.y == y1)
                continue;

            if(line[i].intersectLine(x)){
                y1 = line[i].getY(x);
                if(std::abs(y1) < 0.00001) y1 = 0;
                v1 = Vec2d(x, y1);

                if (v1 == v2)  //问题：如果扫描线正好扫到两条边界线的交点，则此交点不会被填充
                    continue;
                for(int j=i+1; j<line.size(); j++){
                    if(line[j].intersectLine(x)){
                        y2 = line[j].getY(x);
                        v2 = Vec2d(x, y2);
                        if(v1 == v2)   //避免第一层(外层)就扫到了交点上，得到两个一样的坐标
                            continue;
                        inter.push_back(Intersection(v1, v2));  // 完成第一条填充
                        break;
                    }
                }
            }
        }
    }
}

void Layer::printFillingLines() {
    for(int i=0; i<inter.size();i++)
        std::cout << inter[i] << '\n';
}


#endif //IMPROVEVERSION_FILLINGALGORITHM_HH
