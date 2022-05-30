#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>

enum {
    modG90 = 1,
    modG91 = 2
};

class Manipulator {
    double posX;
    double posY;
    double posZ;
    int mod = modG90;

public:
    
    Manipulator(double i_x = 0, double i_y = 0, double i_z = 0) : posX(i_x), posY(i_y), posZ(i_z) {}

    void moveX(double displacement) {
        if (mod == modG90) {
            posX = displacement;
        } else if (mod == modG91) {
            posX += displacement;
        }
    }
    
    void moveY(double displacement) {
        if (mod == modG90) {
            posY = displacement;
        } else if (mod == modG91) {
            posY += displacement;
        }
    }
    
    void moveZ(double displacement) {
        if (mod == modG90) {
            posZ = displacement;
        } else if (mod == modG91) {
            posZ += displacement;
        }
    }

    void readLine(std::string& strCommand) {
        if (strCommand.length() < 2) {
            return;
        }
        std::vector<std::string> command;
        int i = -1;
        for (auto iter = strCommand.begin(); iter != strCommand.end(); ++iter) {
            if (*iter >= 'A' and *iter <= 'Z') {
                ++i;
                command.push_back("");
                command[i].push_back(*iter);
            } else if (*iter == 10) {
            } else {
                command[i].push_back(*iter);
            }
        }
        for (auto str : command) {
            //std::cout << "\n" << str;
            getCommand(str);
        }
    }

    void getCommand(std::string command) {
        std::string tmpStr;
        if (command == "G90") {
            mod = modG90;
        } else if (command == "G91") {
            mod = modG91;
        } else if (command[0] == 'X') {
            tmpStr = command.substr(1, command.length()-1);
            moveX(std::stod(tmpStr));
        } else if (command[0] == 'Y') {
            tmpStr = command.substr(1, command.length()-1);
            moveY(std::stod(tmpStr));
        } else if (command[0] == 'Z') {
            tmpStr = command.substr(1, command.length()-1);
            moveZ(std::stod(tmpStr));
        } else {
            //std::cout << "\nelse " << command;
        }
        //std::cout << "\n" << posX << " " <<  posY << " " <<posZ << " " << "\n";
    }

    double getPosX() const {return posX;}
    double getPosY() const {return posY;}
    double getPosZ() const {return posZ;}
    

};

std::ostream& operator<<(std::ostream& out, const Manipulator& obj) {
    out << obj.getPosX() << " " << obj.getPosY() << " " << obj.getPosZ();
    return out;
}

int main() {
    Manipulator myObject(10, 10, 10);
    std::ifstream file("test.gc");
    if (!file.is_open()) {
        std::cerr << "haven't file test.gc\n";
        return 1;
    }

    std::string line = "";
    while (!file.eof()) {
        if (file.peek() == ';') {
            while (file.get() != 10) {}
        } else {
            char tmp;
            tmp = file.get();
            if ((tmp >= 'A' and tmp <= 'Z') or (tmp >= '0' and tmp <= '9') or tmp == '.' or tmp == '-' or tmp == 10) {
                line += tmp;
                if (tmp == 10) {
                    //std::cout << line;
                    myObject.readLine(line);
                    line = "";
                }
            } else if (tmp != EOF) {
                std::cerr << "Invalid symbol\n" <<  myObject << "\n";
                return 2;
            }
        }
    }

    std::cout << "\n" << myObject << "\n";

}
