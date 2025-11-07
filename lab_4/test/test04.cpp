#include <iostream>
#include <memory>
#include "../include/rhombus.h"
#include "../include/pentagon.h"
#include "../include/hexagon.h"
#include "../include/array.h"

int main(){
    Array<std::shared_ptr<Figure<double>>> arr;

    auto rh = std::make_shared<Rhombus<double>>();
    rh->setPoint(0,{0,0});
    rh->setPoint(1,{2,0});
    rh->setPoint(2,{3,1});
    rh->setPoint(3,{1,1});
    if(rh->isCorrect()) arr.push_back(rh);

    auto pent = std::make_shared<Pentagon<double>>();
    pent->setPoint(0,{0,0});
    pent->setPoint(1,{2,0});
    pent->setPoint(2,{3,2});
    pent->setPoint(3,{1,3});
    pent->setPoint(4,{-1,2});
    if(pent->isCorrect()) arr.push_back(pent);

    auto hex = std::make_shared<Hexagon<double>>();
    hex->setPoint(0,{0,0});
    hex->setPoint(1,{2,0});
    hex->setPoint(2,{3,1});
    hex->setPoint(3,{2,2});
    hex->setPoint(4,{0,2});
    hex->setPoint(5,{-1,1});
    if(hex->isCorrect()) arr.push_back(hex);

    std::cout << "\n=== Initial figures ===\n";
    arr.printAll();
    std::cout << "Total area: " << arr.totalArea() << "\n";

    arr.remove(1);

    std::cout << "\n=== After removal ===\n";
    arr.printAll();
    std::cout << "Total area: " << arr.totalArea() << "\n";

    Array<std::shared_ptr<Figure<double>>> copyArr = arr;
    std::cout << "\n=== Copied array ===\n";
    copyArr.printAll();

    return 0;
}
