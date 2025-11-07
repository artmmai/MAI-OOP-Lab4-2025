#include <iostream>
#include <memory>
#include "include/array.h"
#include "include/rhombus.h"
#include "include/pentagon.h"
#include "include/hexagon.h"

void printMenu() {
    std::cout << "\n=== MENU ===\n"
              << "1. Add Rhombus\n"
              << "2. Add Pentagon\n"
              << "3. Add Hexagon\n"
              << "4. Remove Figure by index\n"
              << "5. Print all figures\n"
              << "6. Total area\n"
              << "7. Exit\n"
              << "============\n"
              << "Choose option: ";
}

int main() {
    Array<std::shared_ptr<Figure<int>>> arr;
    int choice;

    while(true){
        printMenu();
        std::cin >> choice;
        if(!std::cin){ std::cin.clear(); std::cin.ignore(10000,'\n'); continue; }

        if(choice==1){
            auto p = std::make_shared<Rhombus<int>>();
            std::cout << "Enter 4 points (x y):\n";
            std::cin >> *p;
            if(!p->isCorrect()) std::cout << "Invalid rhombus!\n";
            else { arr.push_back(p); std::cout << "Added.\n"; }
        }
        else if(choice==2){
            auto p = std::make_shared<Pentagon<int>>();
            std::cout << "Enter 5 points (x y):\n";
            std::cin >> *p;
            if(!p->isCorrect()) std::cout << "Invalid pentagon!\n";
            else { arr.push_back(p); std::cout << "Added.\n"; }
        }
        else if(choice==3){
            auto h = std::make_shared<Hexagon<int>>();
            std::cout << "Enter 6 points (x y):\n";
            std::cin >> *h;
            if(!h->isCorrect()) std::cout << "Invalid hexagon!\n";
            else { arr.push_back(h); std::cout << "Added.\n"; }
        }
        else if(choice==4){
            size_t idx;
            std::cout << "Enter index: "; std::cin >> idx;
            try { arr.remove(idx); std::cout << "Removed.\n"; }
            catch(...){ std::cout << "Invalid index.\n"; }
        }
        else if(choice==5) arr.printAll();
        else if(choice==6) std::cout << "Total area: " << arr.totalArea() << "\n";
        else if(choice==7) break;
        else std::cout << "Unknown command!\n";
    }

    return 0;
}
