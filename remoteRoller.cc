#include "remoteRoller.h"
#include <iostream>
#include "waterpolyexception.h"

RemoteRoller::RemoteRoller(std::string name, std::vector<std::shared_ptr<Player>> *players,
    std::map<int, std::shared_ptr<Building>> *buildings):Item{name, players, buildings}{}

void RemoteRoller::event(Player& p){
    if (p.canRoll){
        std::cerr << "please input two numbers in range of 1-6" << std::endl;
        int cnt = 0;
        int read1 = 0;
        int sum = 0;
        while(true){
            std::cin >> read1;
            if (read1 <= 6 && read1 >= 0){
                cnt++;
                sum += read1;
                if (cnt == 2) {
                    p.move(sum);
                    p.canRoll = false;
                    break;
                }
            }   else {
                std::cerr << "sorry, your number input is not in the range" << std::endl;
            }
        }
    }   else {
        std::cerr << "sorry, you can not roll" << std::endl;
        throw WaterpolyException("cannot roll");
    }
}

std::shared_ptr<Item> RemoteRollerFactory::produceItem(std::string name){
    return std::make_shared<RemoteRoller>(name, players, buildings);
}

