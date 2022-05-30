#include <iostream>
#include <cmath>

class Point {
    int posX, posY;

public:
    Point(int i_x, int i_y) : posX(i_x), posY(i_y) {}
    int getPosX() {return posX;}
    int getPosY() {return posY;}
};

class Manipulator{
    int basePosX;
    int basePosY;
    int radius;
    double distanceForPoint;
    bool outOfRange = false;

public:

    Manipulator(int i_x, int i_y, int i_r) : basePosX(i_x), basePosY(i_y), radius(i_r) {}

    void calculateDistance(Point& targetPoint) {
        distanceForPoint = std::sqrt(std::pow(targetPoint.getPosX()-basePosX, 2)+std::pow(targetPoint.getPosY()-basePosY, 2));
        if (distanceForPoint > radius) {
            outOfRange = true;
        } 
    }

    double getDistance() {return distanceForPoint;}
    bool getOutOfRange() {return outOfRange;}
};

int main() {
    int posX, posY, rad;
    std::cout << "insert position X, Y and work radius for first manipulator:\n";
    std::cin >> posX >> posY >> rad;
    Manipulator manipulator1(posX, posY, rad);

    std::cout << "insert position X, Y and work radius for second manipulator:\n";
    std::cin >> posX >> posY >> rad;
    Manipulator manipulator2(posX, posY, rad);

    std::cout << "insert position X, Y for target point:\n";
    std::cin >> posX >> posY;
    Point trgPoint(posX, posY);
    
    manipulator1.calculateDistance(trgPoint); 
    manipulator2.calculateDistance(trgPoint); 

    if (manipulator1.getOutOfRange() && manipulator2.getOutOfRange()) {
        std::cout << "Out of range\n";
    }  else if (!manipulator1.getOutOfRange() && manipulator2.getOutOfRange()) {
        std::cout << "work manipulator1\n";
    } else if (manipulator1.getOutOfRange() && !manipulator2.getOutOfRange()) {
        std::cout << "work manipulator2\n";
    } else if (manipulator1.getDistance() == manipulator2.getDistance()) {
        std::cout << "distance equal\n";
    } else if (manipulator1.getDistance() < manipulator2.getDistance()) {
        std::cout << "work manipulator1\n";
    } else {
        std::cout << "work manipulator2\n";
    }
}
