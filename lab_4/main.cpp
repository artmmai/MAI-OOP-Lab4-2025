#include <iostream>
#include <memory>

#include "include/array.h"
#include "include/hexagon.h"
#include "include/pentagon.h"
#include "include/romb.h"

void printMenu() {
    std::cout << "\n=== MENU ===\n"
              << "1. Add Romb\n"
              << "2. Add Pentagon\n"
              << "3. Add Hexagon\n"
              << "4. Remove Figure by index\n"
              << "5. Print all figures\n"
              << "6. Total area\n"
              << "7. Demonstrate template arrays\n"
              << "0. Exit\n"
              << "============\n"
              << "Choose option: ";
}

int main() {
    Array<std::shared_ptr<Figure<double>>> figures;
    int choice;

    while (true) {
        printMenu();
        std::cin >> choice;

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        try {
            if (choice == 1) {
                auto romb = std::make_shared<Romb<double>>();
                std::cout << "Enter 4 points (x y) for Romb:\n";
                std::cin >> *romb;
                if (!romb->isCorrect()) {
                    std::cout << "Invalid romb!\n";
                } else {
                    figures.push_back(romb);
                    std::cout << "Romb added.\n";
                }
            }
            else if (choice == 2) {
                auto pentagon = std::make_shared<Pentagon<double>>();
                std::cout << "Enter 5 points (x y) for Pentagon:\n";
                std::cin >> *pentagon;
                if (!pentagon->isCorrect()) {
                    std::cout << "Invalid pentagon!\n";
                } else {
                    figures.push_back(pentagon);
                    std::cout << "Pentagon added.\n";
                }
            }
            else if (choice == 3) {
                auto hexagon = std::make_shared<Hexagon<double>>();
                std::cout << "Enter 6 points (x y) for Hexagon:\n";
                std::cin >> *hexagon;
                if (!hexagon->isCorrect()) {
                    std::cout << "Invalid hexagon!\n";
                } else {
                    figures.push_back(hexagon);
                    std::cout << "Hexagon added.\n";
                }
            }
            else if (choice == 4) {
                if (figures.size() == 0) {
                    std::cout << "Array is empty!\n";
                    continue;
                }
                size_t idx;
                std::cout << "Enter index (0-" << figures.size() - 1 << "): ";
                if (!(std::cin >> idx) || idx >= figures.size()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Invalid index!\n";
                } else {
                    figures.remove(idx);
                    std::cout << "Removed.\n";
                }
            }
            else if (choice == 5) {
                if (figures.size() == 0) {
                    std::cout << "No figures to print.\n";
                } else {
                    for (size_t i = 0; i < figures.size(); ++i) {
                        std::cout << "\n=== Figure " << i << " ===\n";
                        figures[i]->print_vertices();
                        std::cout << "Center: (" << figures[i]->centroid().x << ", "
                                  << figures[i]->centroid().y << ")\n";
                        std::cout << "Area: " << static_cast<double>(*figures[i]) << "\n";
                    }
                }
            }
            else if (choice == 6) {
                std::cout << "Total area: " << figures.total_area() << "\n";
            }
            else if (choice == 7) {
                std::cout << "\n=== Template Array Demonstration ===\n";
                Array<std::shared_ptr<Figure<int>>> int_figures;
                int_figures.push_back(std::make_shared<Romb<int>>());
                int_figures.push_back(std::make_shared<Pentagon<int>>());
                std::cout << "Array<Figure<int>> total area: " << int_figures.total_area() << "\n";
                
                Array<std::shared_ptr<Hexagon<float>>> hex_array;
                hex_array.push_back(std::make_shared<Hexagon<float>>());
                std::cout << "Array<Hexagon<float>> total area: " << hex_array[0]->area() << "\n";
            }
            else if (choice == 0) {
                std::cout << "Exiting...\n";
                break;
            }
            else {
                std::cout << "Unknown command!\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}