#ifndef _GRID_
#define _GRID_

#include "player.h"
#include "buildings.h"
#include <memory>
#include <vector>
#include <string>
#include "observer.h"
#include <istream>
#include <map>
#include "board.h"
#include <sstream>
class Subject;

class Grid : public Observer{
    private:
        
        int index = -1;
        std::shared_ptr<Board>textDisplay;
        std::vector<std::shared_ptr<Player>> players;
        std::map<int, std::shared_ptr<Building>> buildings;
        
        void auctionPeriod(Subject& whoBankrupt);
        void auctionNeeded(Subject& player);
        
        int propertyindex[28] = {1,3,5,6,8,9,11,12,13,14,15,16,18,19,21,23,24,25,26,27,28,29,31,32,34,35,37,39};


    public:
        std::vector<std::shared_ptr<Player>> currentPlayers();
        std::shared_ptr<Player> findPlayer(std::string name);
        bool isend;
        bool isquit;
        void addPlayer(std::string player,int order);
        void initBuildings();
        void initBoard();
        void initStores();
        std::shared_ptr<Player> nextTurn();    //might change to return a player pointer
        void notify(Subject& whoNotified) override;
        std::map<char, std::shared_ptr<Player>> currentPlayers() const;
        void save(std::string filename);
        void load(std::ifstream &is);
        void displayAllAssets();
        void displayBoard();
        std::map<int, std::shared_ptr<Building>>* getBuildings();

};


#endif


