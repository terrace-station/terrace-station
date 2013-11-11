#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <list>

#include "station.hh"

int main()
{
    std::cout << "Perform some tests:" << std::endl;
    std::cout << "===================" << std::endl;
    Rect rect1(1, 1, 3, 4);
    std::cout << rect1.str() << std::endl;
    Rect rect2(2, 2, 8, 10);
    std::cout << rect2.str() << std::endl;
    std::cout << "Do these rects intersect? " << rect1.intersects(rect2) << std::endl;
    std::list<Rect> rects1;
    rects1.push_back(rect1);
    rects1.push_back(rect2);
    Room room1("corridor", rects1);
    std::cout << room1.str() << std::endl;
    Rect rect3(8, 2, 13, 7);
    std::cout << rect3.str() << std::endl;
    std::list<Rect> rects2;
    rects2.push_back(rect3);
    Room room2("laboratory", rects2);
    std::cout << room2.str() << std::endl;
    std::cout << "Do these rooms intersect? " << room1.intersects(room2) << std::endl;
}
