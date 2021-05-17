#include "nonproperty.h"

class MoneyException;

void NonProperty::dcPay50(Player& p) {
    try {
    p.setMoney(-50);
    p.leaveLine();
    } catch (MoneyException &me) {
        std::cout << "Money is not enough to pay $50! " << std::endl;
        me.isForcible=true;
        p.oweBank();
        throw;
    }
}

void NonProperty::dcUseCup(Player& p) {
    p.setDCCups(-1);
    p.leaveLine();
}

void NonProperty::dcthreefail(Player& p) {
    std::cout << "You can only choose from these options to leave the line:" << std::endl;
    std::cout << "Option 1: Pay $50 immediately." <<std::endl;
    std::cout << "Option 2: Use a Roll Up the Rim cup. ";
    std::cout << "You have " << p.getDCCups() << " cup(s)."<< std::endl;
    char ans;
    while (true) {
        if (std::cin >> ans) {
            if (ans == '1') {
                dcPay50(p);
                break;
            } else if (ans == '2') {
                if (p.getDCCups() == 0) {
                    std::cout << "You do not have enough Roll Up the Rim cups." << std::endl;
                    std::cout << "Please choose option 1 by entering \"1\"." << std::endl;
                } else {
                    dcUseCup(p);
                    break;
                }
            } else {
                std::cout << "Invalid input. Please enter number: 1 or 2." << std::endl;
            }
        }
    }
}

void NonProperty::dctimsline(Player& p) {
    if (p.inLine() == true) {
            std::cout << "You can choose from these options to leave the line:" << std::endl;
            std::cout << "Option 1: Roll dices and if you roll double, you can leave the line. Otherwise, wait for next turn." << std::endl;
            std::cout << "Option 2: Pay $50 immediately." <<std::endl;
            std::cout << "Option 3: Use a Roll Up the Rim cup. ";
            std::cout << "You have " << p.getDCCups() << " cup(s)."<< std::endl;
            std::cout << "Please enter number: 1, 2 or 3."<< std::endl;
            char ans;
            while (true) {
                if (std::cin >> ans) {
                    if (ans == '1') {
                        int roll1 = rollnum1();
                        int roll2 = rollnum2();
                        int sum = roll1+roll2;
                        if (roll1 == roll2) {
                            p.leaveLine();
                            std::cout << "Congratulations! You get off the line."<< std::endl;
                        } else {
                            if (p.timesInDC() == 3) {
                                dcthreefail(p);
                                p.move(sum);
                                p.canRoll = false;
                            } else {
                                p.addTimTurn();
                                std::cout << "Sorry! You need to wait for the next turn."<< std::endl;
                            }
                        }
                        break;
                    } else if (ans == '2') {
                        dcPay50(p);
                        break;
                    } else if (ans == '3') {
                        if (p.getDCCups() == 0) {
                        std::cout << "You do not have enough Roll Up the Rim cups." << std::endl;
                        std::cout << "Please choose another option." << std::endl;
                        } else {
                            dcUseCup(p);
                            break;
                        }
                    } else {
                        std::cout << "Invalid input. Please enter number: 1, 2 or 3." << std::endl;
                    }
                }
            }
        }
}

NonProperty::NonProperty(std::string name, int position): 
Building(name, position) {}

NonProperty::~NonProperty() {}

void NonProperty::event(Player &p) {
    if (hasMine){
        p.nextCanRoll = false;
        std::cout << "Boom! it hurts! Next turn you can not move!" << std::endl;
    }
    if (getInfo().name == "Collect OSAP") {
        p.collectOSAP();
    } else if (getInfo().name == "DC Tims Line") {
        dctimsline(p);
    } else if (getInfo().name == "GO TO TIMS") {
        p.goTim();
    } else if (getInfo().name == "GOOSE NESTING") {
        std::cout << "Oops. You are attacked by a flock of nesting geese." <<std::endl;
    } else if (getInfo().name == "COOP FEE") {
        try {
        p.setMoney(-150);
        } catch (MoneyException &we) {
            std::cout << "Money is not enough to pay $150! ";
            we.isForcible=true;
            p.oweBank();
            throw;
        }
    } else if (getInfo().name == "TUITION") {
        std::cout << "You arrived \"Tuition\" Square." <<std::endl;
        std::cout << " You can choose between" << std::endl;
        std::cout << "A. paying $300 tuition " << std::endl;
        std::cout << "B. 10% of your total worth (including your savings, printed prices of all buildings you own, and costs of each improvement)." << std::endl;
        std::cout << "Please enter \"A\" or \"B\"." << std::endl;
        char ans;
            while (true) {
                if (std::cin >> ans) {
                    if (ans == 'A') {
                        try {
                        p.setMoney(-300);
                        std::cout << "$300 is paid. ";
                        break;
                        }
                        catch (MoneyException &we) {
                        std::cout << "Money is not enough to pay $300! ";
                        we.isForcible=true;
                        p.oweBank();
                        throw;
                        }
                    } else if (ans == 'B') {
                        int totalworth = p.totalWorth();
                        try {
                            int val = totalworth/10;
                            p.setMoney(-val);
                            std::cout << "$" << val << " is paid. ";
                            break;
                        }
                        catch (MoneyException &we) {
                        std::cout << "Cash is not enough to pay 10% of your total worth! ";
                        we.isForcible=true;
                        p.oweBank();
                        throw;
                        }
                    } else {
                        std::cout << "Invalid input. Please enter \"A\" or \"B\"." << std::endl;
                    }
                }
            }

    }
}

void NonProperty::load (std::string buildstr, Player * owner) {}


std::string NonProperty::save() {
    return "";
}
