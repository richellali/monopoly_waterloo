#include "grid.h"
#include "buildingexception.h"
#include "monopolyexception.h"
#include "monopolyexception.h"
#include "roll.h"
#include <fstream>
using namespace std;

enum type{Roll, trade, improve, mortgage, unmortgage, bankrupt, assets, all, save, use,invalid, quit};
bool isPlayer(char c){
    if (c == 'G' || c == 'B' || c == 'D' || c == 'P' || 
    c == 'S' || c == '$' || c == 'L' || c == 'T') return true;
    return false;
}

type getType(string cmd){
    if (cmd == "roll") return Roll;
    if (cmd == "trade") return trade;
    if (cmd == "improve") return improve;
    if (cmd == "mortgage") return mortgage;
    if (cmd == "unmortgage") return unmortgage;
    if (cmd == "bankrupt") return bankrupt;
    if (cmd == "assets") return assets;
    if (cmd == "all") return all;
    if (cmd == "save") return save;
    if (cmd == "use") return use;
    if (cmd == "quit") return quit;
    return invalid;
 }



int main(int argc, char const *argv[])
{   
    std::string cmdline;
    bool testing_model = false;
    bool load_model = false;
    std::string loadfile;
    for (int i = 1; i < argc; i ++){
        cmdline = argv[i];
        if (cmdline == "-testing") testing_model = true;
        if (cmdline == "-load" && i+1 < argc){
            loadfile = argv[i+1];
        }
    }
    std::ifstream infile{loadfile};
    if (!infile.fail()) load_model = true;          //if this file can be opened, then loadmodel is true
    
    std::cin.exceptions(ios::failbit|ios::eofbit);
    string s;
    int playerNum;
    std::shared_ptr<Player> currentPlayer = nullptr;
    cout << "----------------Game Begin----------------" << endl;
    if (testing_model) cout << "testing model is on!" << endl;

    auto grid = std::make_shared<Grid>();
    grid->initBuildings();
    std::string cmd;
    std::string arg1;
    std::string arg2;
    std::string arg3;
    std::string answer1;
    int arg4;
    std::shared_ptr<Player> tradeTarget = nullptr;
    istringstream iss;
    istringstream temp;
    int rollNum1 = 0;
    int rollNum2 = 0;
    if (!load_model){
        cout << "please input the number of players! (6~8)" << endl;        //init players part
        while(1){
            try{
                std::cin >> playerNum;
                if (playerNum >= 6 && playerNum <= 8){
                    break;
                }
                std::cerr << "your input is not in the valid range, please input again!" << endl;
            }   catch (ios::failure){
                std::cin.clear();
                std::cin.ignore();
                std::cerr << "invalid input, please input again!" << endl;
            }
        }
        cout << "Please choose names of players: G B D P S $ L T" << endl;
        cout << "please input the names of the " << playerNum << " players!" << endl;
        int i = 0;
        while (i < playerNum){
            try{
                std::cin >> s;
                if (isPlayer(s.at(0)) && !grid->findPlayer(s)){
                    grid->addPlayer(s,i);
                    i++;
                }   else {
                    std::cerr << "The name your input is not a valid player name, please do that again!" << endl;
                }
            }   catch (ios::failure){
                std::cin.clear();
                std::cin.ignore();
                std::cerr << "invalid input, please input again!" << endl;
            }
        }
    }   else {
        //grid.initBoard();
        grid->load(infile);
    }
    grid->initBoard();
    auto allplayers = grid->currentPlayers();
        for (auto &p : allplayers){
            p->attach(grid);
        }
    while(true){                         //game period
        currentPlayer = grid->nextTurn();
        if (!currentPlayer->nextCanRoll){
                currentPlayer->nextCanRoll = true;
                currentPlayer->canRoll = false;
            }
        int liabilities = 0;
        if (grid->isend){
             std::cerr << "The Winner is " << currentPlayer->getInfo().name << "!!!" << endl;
             std::cerr << "Congradulations!!!" << endl;
             break;
        }
        if (grid->isquit){
             break;
        }
        while(true){
            if (currentPlayer->isBankrupted()) break;
            std::cerr << "Hey Player " << currentPlayer->getInfo().name << "! What you want to do?" << endl;
            std::cerr << "Please enter the following cmd: roll trade improve mortgage "<<
            "unmortgage bankrupt assets all save use." << " If you are finished, you can enter next."<< endl;
            std::cout << "If you want to quit the game, you can enter quit. But remember to save first if you want to continue playing."<< endl;
            grid->displayBoard();
            
            std::cin >> cmd;
            if (cmd == "quit") {
                grid->isquit = true;
                break;
            }
            if (cin.eof()){
                grid->isquit = true;
                break;
            }
            if (cmd == "next" && !currentPlayer->canRoll) {
                
                // setting liabilities
                if (currentPlayer->getMoney() < -liabilities) {
                    currentPlayer->declareBankrupt(); // ->
                } else {
                    currentPlayer->setMoney(liabilities);
                }
                currentPlayer->canRoll = true;
                break;
            }
            switch (getType(cmd))
            {
            case Roll:
                if (currentPlayer->canRoll){
                    int rolltotal = 0;
                    if (testing_model){
                        int num1,num2;
                        while (true) {
                            try {
                                cin >>num1 >>num2;
                                if (num1 <0 || num2 < 0) {
                                cout << "Invalid die value. Enter another two non-negative numbers please." << endl;
                                int error = -1;
                                throw error;
                                }
                                break;
                            } catch (std::ios::failure &) {
                                cout << "Invalid die value. Enter another two non-negative numbers please." << endl;
                                std::cin.clear();
                                std::cin.ignore();
                            }
                             catch (int& error) {
                                 cout << "Invalid die value. Enter another two non-negative numbers please." << endl;
                                 std::cin.clear();
                                 std::cin.ignore();
                            }
                        }
                        rolltotal = num1 + num2;
                        cout << "Your total is " << rolltotal << endl;
                    }  else {
                        rollNum1 = rollnum1();
                        rollNum2 = rollnum2();
                        rolltotal = rollNum1 + rollNum2;
                        if (rollNum1 == rollNum2) {
                            cout << "You rolled double! Enter any one character to roll again."<< endl;
                            char k; 
                            cin >> k;
                            int rollNum3 = rollnum3();
                            int rollNum4 = rollnum4();
                            rolltotal += rollNum3;
                            rolltotal += rollNum4;
                            currentPlayer->rollDouble += 1;
                            if (rollNum3 == rollNum4) {
                                cout << "You rolled double! Enter any one character to roll again."<< endl;
                                char f; 
                                cin >> f;
                                int rollNum5 = rollnum5();
                                int rollNum6 = rollnum6();
                                rolltotal += rollNum5;
                                rolltotal += rollNum6;
                                currentPlayer->rollDouble += 1;
                                if (rollNum5 == rollNum6) {
                                currentPlayer->goTim();
                                break;
                                }
                            }
                        }
                        cout << "Your total is " << rolltotal << endl;
                    }
                        try {
                            if (!currentPlayer->inLine()) {
                                currentPlayer->move(rolltotal);
                            } else {
                                currentPlayer->stayInTim();
                                break;
                            }
                        } catch (MoneyException &m) {
                            
                            if (m.isForcible) {
                                liabilities = m.getChange();
                                std::cerr << "Sorry, you don't have enough money to pay. Please mortgage your "
                                << "building, sell improvement or trade with others, otherwise, you need to "
                                << "decare bankrupt." << endl; 
                            }
                            
                        } catch (BuildingException &be) {
                            
                        } 
                        currentPlayer->canRoll = false;
                    }
                    else {
                    std::cerr << "sorry, you have already rolled!" << endl;
                }
                
                break;
            case trade:
                std::cin >> arg1;
                tradeTarget = grid->findPlayer(arg1);
                
                std::cin >> arg2 >> arg3;
                //cout << arg2 << "this is arg2" << endl;
                //cout << arg3 << "this is arg3" << endl;
                if (tradeTarget == nullptr) {
                    std::cerr << "This player does not exist. Please enter again." << endl;
                    break;
                }
                try {
                    try{
                        arg4 = stoi(arg2);
                        //cout << arg4 << "this is arg4"  << endl;
                        currentPlayer->trade(*tradeTarget, arg4, grid->findPlayer(arg1)->getBuilding(arg3));
                        break;
                    }   catch(invalid_argument){
                        try{
                            arg4 = stoi(arg3);
                            //cout << arg4 << "this is arg4"  << endl;
                            currentPlayer->trade(*tradeTarget, currentPlayer->getBuilding(arg2), arg4);
                            break;
                        }   catch(invalid_argument){
                            currentPlayer->trade(*tradeTarget, grid->findPlayer(arg1)->getBuilding(arg3),
                        currentPlayer->getBuilding(arg2));
                            break;
                        }
                    } 
                } catch (MoneyException &me) {
                    std::cerr << "Sorry, you don't have enough money to trade." << endl;
                } catch (BuildingException &be) {
                    std::cerr << "Invalid command." << endl;
                    //cerr << "Sorry, you don't own the building or the building cannot be traded." << endl;
                }
                break;
            case improve:
                std::cin >> arg2;
                std::cin >> arg1;
                if (arg1 == "buy"){
                    try {
                        currentPlayer->improve(currentPlayer->getBuilding(arg2)); 
                    } catch(MoneyException &me) {
                        std::cerr << "You don't have enough money to buy the improvement." << endl;
                    } catch (BuildingException &be) {
                        std::cerr << "Invalid building." << endl;
                    } catch(MonopolyException &moe) {
                        std::cerr << "You don't have the corresponding monoply block to buy the improvement" << endl;
                    }
                }   else if (arg1 == "sell"){
                    try {
                        currentPlayer->sellImprovements(currentPlayer->getBuilding(arg2));
                    } catch (BuildingException) {
                        std::cerr << "The building might be not existed or has no improvement"
                        << " to sell." << endl;
                    }
                }   else {
                    std::cerr << "invalid input" << endl;
                }
                break;
            case mortgage:
                currentPlayer->mortgageList(); // player will enter none if they change their mind
                while(true) {
                    std::cin >> arg1;
                    if (arg1 == "none") break;
                    try {
                        currentPlayer->getBuilding(arg1);
                        currentPlayer->mortgage(currentPlayer->getBuilding(arg1));
                        break;
                    } catch (BuildingException &be) {
                        std::cerr << "You do not own that building or the building cannot be mortgaged. "
                        << "Please change a name or sell all improvement."<< endl;
                    }
                }
                break;
            case unmortgage:
                currentPlayer->unmortgageList();// player will enter none if they change their mind
                while(true) {
                    std::cin >> arg1;
                    if (arg1 == "none") break;
                    try {
                        currentPlayer->unmortgage(currentPlayer->getBuilding(arg1));
                        break;
                        //break;
                    } catch (BuildingException &be) {
                        std::cerr << "You do not own that building or the building cannot be mortgaged. "
                        << "Please change a name or sell all improvement."<< endl;
                    } catch(MoneyException &me) {
                        std::cerr << "You do not have enough money to unmortgage this building." << endl;
                    }
                }
                break;
            case bankrupt:
                if (-liabilities > currentPlayer->getMoney()) {
                    currentPlayer->declareBankrupt();//      add bankrupt method!! remember to notify observers!
                } else {
                    std::cerr << "Sorry, you have more money than the liability, "
                    << "you cannot declare bankruptcy now." << endl;
                }
                break;
            case assets:
                currentPlayer->displayAsset();
                break;
            case all:
                grid->displayAllAssets();
                break;
            case save:
                std::cin >> arg1;
                grid->save(arg1);
                break;
            case invalid:
                std::cerr << "Invalid command input!" << endl;
                break;
            case use:
                currentPlayer->displayItemList();
                std::cerr << "Please input the index of item you want to use, the first item is 0, input -1 to quit" << endl;
                
                std::cin >> answer1;
                if (answer1 == "-1" ) break;
                if (!(answer1 == "0" || answer1 == "1" ||answer1 == "2" ||answer1 == "3" ||answer1 == "4" ||answer1 == "5" ||answer1 == "6" ||answer1 == "7" ||answer1 == "8" ||answer1 == "9")) {
                    cerr << "Invalid" << endl;
                    break;
                }
                arg4 = stoi(answer1); 
                currentPlayer->useItem(arg4);
                break;
            default:
                break;
            }
        }
    }   
}


