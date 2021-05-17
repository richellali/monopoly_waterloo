#ifndef _BOARD_
#define _BOARD_

#include<iostream>
#include<vector>
#include<map>
#include <memory>
#include "observer.h"
#include "property.h"
#include <algorithm>
class Building;
class Player;


class Board : public Observer {
    friend std::ostream &operator<<(std::ostream &out, const Board& b);
    private:
        std::map<int, std::vector<std::string>> players;
        std::map<int, std::shared_ptr<Building>>* buildings;
        int propertyindex[28] = {1,3,5,6,8,9,11,12,13,14,15,16,18,19,21,23,24,25,26,27,28,29,31,32,34,35,37,39};
        int length = 8;
    public:
        Board(std::vector<std::string> p, std::map<int, std::shared_ptr<Building>> *b);
        void notify(Subject& whoNotified) override;
        
       

};

std::ostream &operator<<(std::ostream &out, const Board& b);


#endif
