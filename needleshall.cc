#include "needleshall.h"
#include "player.h"
#include "moneyexception.h"
#include <iostream>
#include <cstdlib>

NeedlesHall::NeedlesHall(std::string name, int pos,std::vector<std::shared_ptr<Player>> *players,
    std::map<int, std::shared_ptr<Building>> *buildings): NonProperty{name, pos}, strategy{nullptr}{
        mf.initFactory(players, buildings);
        rf.initFactory(players,buildings);
        mif.initFactory(players,buildings);
    }

void NeedlesHall::shoppingPeriod(Player& p){
    std::string name;
    std::cerr << std::endl << std::endl << "================Shopping Period================" << std::endl;
    std::cerr << "Would you like to buy some items?" << std::endl;
    std::cerr << "RemoteRoller: $200" << std::endl;
    std::cerr << "Missile: $300" << std::endl;
    std::cerr << "Mine: $50" << std::endl;
    std::cerr << "type the name to buy the corresponding items and quit to exit" << std::endl;
    while(true){
        std::cin >> name;
        if (name == "RemoteRoller"){
            try{
                p.setMoney(-200);
                p.addItem(rf.produceItem("RemoteRoller"));
                break;
            }   catch(MoneyException){
                std::cerr << "sorry, you do not have enough money" << std::endl;
            }
        }   else if (name == "Missile"){
            try{
                p.setMoney(-300);
                p.addItem(mf.produceItem("Missile"));
                break;
            }catch(MoneyException){
                std::cerr << "sorry, you do not have enough money" << std::endl;
            }
        }   else if (name == "quit"){
            break;
        }   else if (name == "Mine"){
            try{
                p.setMoney(-50);
                p.addItem(mif.produceItem("Mine"));
                break;
            }catch(MoneyException){
                std::cerr << "sorry, you do not have enough money" << std::endl;
            }
        }   else {
            std::cerr << "invalid input" << std::endl;
        }  
    }
}

void NeedlesHall::event(Player & p) {
    std::cerr << "Welcome to Needles Hall!" << std::endl;

    int probability = std::rand() % 100;
    // rare prob(1%) of receving a dc cup and leave SLC
    if (probability == 1 && p.getDCCups() < 4) {
        std::cerr << "Congratulation! You receive a winning Roll Up the Rim cup! "
         << "You can use it for leave the DC Tims line for free!" << std::endl;
        shoppingPeriod(p);
        p.setDCCups(1);
        return;
    }

    probability = std::rand() % 18;
    if (probability < 1) {
        strategy = std::make_unique<L200>();
    } else if (probability < 3) {
        strategy = std::make_unique<L100>();
    } else if (probability < 6) {
        strategy = std::make_unique<L50>();
    } else if (probability < 12) {
        strategy = std::make_unique<W25>();
    } else if (probability < 15) {
        strategy = std::make_unique<W50>();
    } else if (probability < 17) {
        strategy = std::make_unique<W100>();
    } else {
        strategy = std::make_unique<W200>();
    }
    try {
        strategy->dosth(p);
    } catch (MoneyException &me) {
        p.oweBank();
        me.isForcible = true;
        throw;
    }
    shoppingPeriod(p);

}


void L200::dosth(Player & player) {
    std::cerr << "Sorry, you lose 200 dollars :(" << std::endl;
    try{
        player.setMoney(-200);
    } catch (MoneyException) {
        std::cerr << "You don't have enough money to pay." << std::endl;
        throw;
    }
}

void L100::dosth(Player & player) {
    std::cerr << "Sorry, you lose 100 dollars :(" << std::endl;
    try{
        player.setMoney(-100);
    } catch (MoneyException) {
        std::cerr << "You don't have enough money to pay." << std::endl;
        throw;
    }
}

void L50::dosth(Player & player) {
    std::cerr << "Sorry, you lose 50 dollars :(" << std::endl;
    try{
        player.setMoney(-50);
    } catch (MoneyException) {
        std::cerr << "You don't have enough money to pay." << std::endl;
        throw;
    }
}

void W25::dosth(Player & player) {
    std::cerr << "Congratulation, you win 25 dollars :)" << std::endl;
    player.setMoney(25);
}

void W50::dosth(Player & player) {
    std::cerr << "Congratulation, you win 50 dollars :)" << std::endl;
    player.setMoney(50);
}

void W100::dosth(Player & player) {
    std::cerr << "Congratulation, you win 100 dollars :)" << std::endl;
    player.setMoney(100);
}

void W200::dosth(Player & player) {
    std::cerr << "Congratulation, you win 200 dollars :)" << std::endl;
    player.setMoney(200);
}

