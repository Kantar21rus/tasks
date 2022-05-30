#include <iostream>
#include <cmath>

class Manipulator;

class Point {
    double posX, posY;
    Manipulator* whichManipulatorTake = nullptr;

public:
    Point(double i_x, double i_y) : posX(i_x), posY(i_y) {}
    double getPosX() {return posX;}
    double getPosY() {return posY;}
    void setManipulator(Manipulator* ptrManipulator) {whichManipulatorTake = ptrManipulator;}
    int getManipulatorId();
};

class Manipulator{
    double PosX;
    double PosY;
    double radius;
    int id;
    double distanceForPoint;
    bool outOfRange = false;

public:

    Manipulator(double i_id, double i_x, double i_y, double i_r) : id(i_id), PosX(i_x), PosY(i_y), radius(i_r) {}

    void calculateDistance(Point& targetPoint) {
        distanceForPoint = std::sqrt(std::pow(targetPoint.getPosX()-PosX, 2)+std::pow(targetPoint.getPosY()-PosY, 2));
        if (distanceForPoint > radius) {
            outOfRange = true;
        } 
    }
    
    void moveManipulator(double i_x, double i_y) {
        PosX = i_x;
        PosY = i_y;
    }

    double getDistance() {return distanceForPoint;}
    bool getOutOfRange() {return outOfRange;}
    int getId() {return id;}
};

int Point::getManipulatorId() {
    return whichManipulatorTake->getId();
}

int main() {
    Manipulator manipulator1(1, 0, 0, 4);
    
    Manipulator manipulator2(2, 2, 1, 3);
    

    Point trgPoint[5] = {{1,3},{2,1.41},{0.2, -7}, {-5, -1}, {0, 9}};
    
    for (int i=0; i < 5; ++i) {
        manipulator1.calculateDistance(trgPoint[i]); 
        manipulator2.calculateDistance(trgPoint[i]); 

        if (manipulator1.getOutOfRange() && manipulator2.getOutOfRange()) {
            if (manipulator1.getDistance() <= manipulator2.getDistance()) {
                manipulator1.moveManipulator(trgPoint[i].getPosX(), trgPoint[i].getPosY());
                trgPoint[i].setManipulator(&manipulator1); 
            } else {
                manipulator2.moveManipulator(trgPoint[i].getPosX(), trgPoint[i].getPosY());
                trgPoint[i].setManipulator(&manipulator2); 
            }
        } else if (!manipulator1.getOutOfRange() && manipulator2.getOutOfRange()) {
            manipulator1.moveManipulator(trgPoint[i].getPosX(), trgPoint[i].getPosY());
            trgPoint[i].setManipulator(&manipulator1); 
        } else if (manipulator1.getOutOfRange() && !manipulator2.getOutOfRange()) {
            manipulator2.moveManipulator(trgPoint[i].getPosX(), trgPoint[i].getPosY());
            trgPoint[i].setManipulator(&manipulator2); 
        } else {
            if (manipulator1.getDistance() <= manipulator2.getDistance()) {
                trgPoint[i].setManipulator(&manipulator1); 
            } else {
                trgPoint[i].setManipulator(&manipulator2); 
            }
        }
    }
    std::cout  << "\t\t";
    for (int i=1; i < 6; ++i) {
        std::cout << i << "\t ";
    }
    std::cout << "\nmanipulator1:\t";
    for (int i=0; i < 5; ++i) {
        if (trgPoint[i].getManipulatorId() == manipulator1.getId()) {
            std::cout << "{" << trgPoint[i].getPosX() << ", " << trgPoint[i].getPosY()<< "}";
        } else {
            std::cout << " \t ";
        }
    }
    std::cout <<  "\n";
    std::cout << "manipulator2:\t";
    for (int i=0; i < 5; ++i) {
        if (trgPoint[i].getManipulatorId() == manipulator2.getId()) {
            std::cout << "{" << trgPoint[i].getPosX() << ", " << trgPoint[i].getPosY()<< "}";
        } else {
            std::cout << " \t ";
        }
    }
    std::cout <<  "\n";
}
