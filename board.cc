#include "board.h"
#include "subject.h"
#include "property.h"

Board::Board(std::vector<std::string> p, std::map<int, std::shared_ptr<Building>> *b){
    players[0] = p;
    buildings = b;
}

void Board::notify(Subject & whoNotified){
    std::string name = whoNotified.getInfo().name;
    for (auto &p : players){
        auto index = std::find(p.second.begin(), p.second.end(), name);
        if ( index != p.second.end()){
            p.second.erase(index);
            if (!whoNotified.getInfo().isBankrupt){
                players[whoNotified.getInfo().position].emplace_back(name);
            }
            return;
        }
    }
}


int convert(int i, int j){
    if (j == 0){
        return 10 + (10-i);
    } else {
        if (i == 0){
            return 20 + j;
        }   else if (i == 10){
            return 10 - j;
        }   else {
            return 30 + i;
        }
    }
}

std::ostream &operator<<(std::ostream &out, const Board& b){
    auto players = b.players;
    auto buildings = *b.buildings;
    for (int i = 0; i < 56; i++){
        for (int j = 0; j < 11; j++){
            if (i != 0 && i != 55){
                if (j == 0) out << '|';
            }   else {
                out << '-';                 //add an addition '-'
            }
            for (int k = 0; k < b.length; k++){
                if (i == 0 || i == 55){
                    if (k != b.length-1){
                    out << '-';                         // when i == 0 || 55 print "-------"
                    } 
                    if (k == 0 && j ==0) {
                        out << '-';         // add an addition '-'
                    }
                } else if (i == 5){
                    if (k == b.length-1 && i == 5){
                        out << '|';
                    }  else {
                        out << '_';
                    }         
                }   else if (i < 5){            //when i < 5, print the blocks
                     if (i == 1 && k ==0){
                        if (j == 0){
                            out << "Goose";
                            k += 5;
                        }   else if (j == 2){
                            out << "NEEDLES";
                            k += 7;
                        }   else if (j == 5){
                            out << "V1";
                            k+= 2;
                        }   else if (j == 8){
                            out << "CIF";
                            k+=3;
                        }   else if (j == 10){
                            out << "GO TO";
                            k+=5;
                            }   else{
                                auto property = dynamic_cast<AcademicBuilding&>(*(buildings[convert(i/5,j)]));
                                int level = property.getImprovedLevel();
                                for (int p = 0; p < level; p++){
                                    out << "I";
                                    k++;
                                }
                            }
                        }
                     else if (i == 2 && k ==0){
                        if (j == 0){
                            out << "Nesting";
                            k += 7;
                        }   else if (j == 2 ){
                            out << "HALL";
                            k+=4;                        
                        }   else if (j == 5){}     //it will go to the else condition below and print ' '
                            else if (j == 8){}
                            else if (j == 10){
                                out << "TIMS";
                                k += 4;
                            }   else {
                                out << "-------";
                                k += 7;
                            }
                        }
                    else if (i == 3 && k ==0){
                        //if (j == 0) add player display
                        if (j == 1){
                            out << "EV1";
                            k += 3;
                            int index = convert(i/5,j);
                            if (!players[index].empty()){
                                out << "   ";
                                out << players[index].front();
                                k += 4;
                            }
                        }   else if (j == 3){
                            out << "EV2";
                            k += 3;
                            int index = convert(i/5,j);
                            if (!players[index].empty()){
                                out << "   ";
                                out << players[index].front();
                                k += 4;
                            }
                        }   else if (j == 4){
                            out << "EV3";
                            k += 3;
                            int index = convert(i/5,j);
                            if (!players[index].empty()){
                                out << "   ";
                                out << players[index].front();
                                k += 4;
                            }
                        }   else if (j == 6){
                            out << "PHYS";
                            k += 4;
                            int index = convert(i/5,j);
                            if (!players[index].empty()){
                                out << "  ";
                                out << players[index].front();
                                k += 3;
                            }
                        }   else if (j == 7){
                            out << "B1";
                            k += 2;
                            int index = convert(i/5,j);
                            if (!players[index].empty()){
                                out << "   ";
                                out << players[index].front();
                                k += 4;
                            }
                        }   else if (j ==9){
                            out << "B2";
                            k += 2;
                            int index = convert(i/5,j);
                            if (!players[index].empty()){
                                out << "   ";
                                out << players[index].front();
                                k += 4;
                            }
                        }   else {
                            int index = convert(i/5,j);
                            if (!players[index].empty()){
                                int size = (players[index].size() < 8) ? players[index].size() : 7;
                                    for (int p = 0; p < size; p++){
                                        out << players[index].at(p);
                                        k++;
                                    }
                            }
                        } 
                    }   else if (i == 4 && k == 0){
                        if (j == 1 || j == 3 || j == 4 || j == 6 ||j == 7 || j ==9){
                            int index = convert(i/5,j);
                            int size = players[index].size();
                            if (size > 1){
                                auto playerIt = players[index].begin();
                                playerIt++;
                                while (playerIt != players[index].end()){
                                    out << *playerIt;
                                    playerIt++;
                                    k++;
                                }
                            }
                        }   else {
                            int index = convert(i/5,j);
                            int size = players[index].size();
                            if (size == 8){
                                out << players[index].back();
                                k++;
                            }
                        }
                    }   
                if (k == b.length-1){
                    out << '|';
                }   else {
                    out << ' ';
                }
            }   else if (i < 24){
                    int index = convert(i/5,j);
                    int size = players[index].size(); 
                    if (k == b.length-1 && j == 0){
                            out << '|';
                        }   else if ((j == 10|| j == 9) && k == b.length-1){
                            out << '|';
                        }   else {
                            if (i == 6 || i == 11 || i == 21 ){
                                if ((j == 0 || j == 10) && k == 0){
                                auto property = dynamic_cast<AcademicBuilding&>(*(buildings[convert(i/5,j)]));
                                int level = property.getImprovedLevel();
                                for (int p = 0; p < level; p++){
                                    if (p == 0)k--;
                                    out << "I";
                                    k++;
                                }
                                if (level == 0) out << ' ';
                                }   else {
                                    out << ' ';
                                }
                            } else{
                                    if (j == 0 || j == 10){
                                        if (i == 10 || i == 15 || i == 20) out << '_';
                                        else if (i == 7 || i == 12 || i == 22)out << '-';
                                        else{
                                           
                                           if (i == 8  && k ==0){
                                                if (j == 0){
                                                    out << "OPT";
                                                    k += 2;
                                                    if (size > 0){
                                                        out << "   ";
                                                        out << players[index].front();
                                                        k += 4;
                                                    }  
                                                }   else if (j == 10){
                                                    out << "EIT";
                                                    k += 2;
                                                    if (size > 0){
                                                        out << "   ";
                                                        out << players[index].front();
                                                        k += 4;
                                                    } 
                                                }
                                        }   else if (i == 13 && k == 0){
                                                    if (j == 0){
                                                out << "BMH";
                                                k += 2;
                                                if (size > 0){
                                                    out << "   ";
                                                    out << players[index].front();
                                                    k += 4;
                                                }
                                            }   else if (j == 10){
                                                out << "ESC";
                                                k += 2;
                                                if (size > 0){
                                                    out << "   ";
                                                    out << players[index].front();
                                                    k += 4;
                                                }
                                            }
                                        }   else if (i == 16 && k == 0){
                                            if (j == 0 || j == 10){
                                                out << "SLC";
                                                k += 2;
                                                if (size > 0){
                                                    out << "   ";
                                                    out << players[index].front();
                                                    k += 4;
                                                }
                                            }
                                        }   else if (i == 23 && k == 0){
                                                if (j == 0){
                                                out << "LHI";
                                                k += 2;
                                                if (size > 0){
                                                    out << "   ";
                                                    out << players[index].front();
                                                    k += 4;
                                                }
                                            }   else if (j == 10){
                                                out << "C2";
                                                k += 1;
                                                if (size > 0){
                                                    out << "    ";
                                                    out << players[index].front();
                                                    k += 5;
                                                }
                                            }
                                        }   else if ((i == 9 || i == 14 || i == 17)) {
                                                if (size > 1 && k == 0 && (j == 0 || j == 10)){
                                                   
                                                    auto playerIt = players[index].begin();
                                                    playerIt++;
                                                    k--;
                                                    while (playerIt != players[index].end()){
                                                        out << *playerIt;
                                                        playerIt++;
                                                        k++;
                                                    }
                                        
                                                }   else {
                                                    out << ' ';
                                                }
                                        
                                        }     else {
                                            out << ' ';
                                        }
                                        }
                                    }   else {
                                        out << ' ';
                                    }
                                }
                            }
                    }   else if (i <= 55){
                            int index = convert(i/5,j);
                            int size = players[index].size();
                        if (k == b.length-1 && j == 0){
                            out << '|';
                        }   else if ((j == 10|| j == 9) && k == b.length-1){
                            out << '|';
                        }   else {
                            if (i == 24){
                                if (size > 1 && k == 0 && (j == 0 || j == 10)){
                                    auto playerIt = players[index].begin();
                                    playerIt++;
                                    k--;
                                    while (playerIt != players[index].end()){
                                        out << *playerIt;
                                        playerIt++;
                                        k++;
                                    }
                                    
                                } else if (j >= 2 && j < 9){
                                    if (j == 2 && k <= 4){
                                        out << ' ';
                                    }   else if (j == 8 && k >= 2){
                                        out << ' ';
                                    }   else {
                                        out << '-';
                                    }
                                }   else {
                                    out << ' ';
                                }   
                            }   else if (i == 25 ){
                                    if (j == 0 || j == 10){
                                        out << '_';
                                    }   else if ((j == 2 && k == 4) || (j == 8 && k ==2)){
                                            out <<'|';
                                    }   else {
                                        out <<' ';
                                    }
                            }   else if (i == 26){
                                if (j == 0 && k == 0){
                                    out << "UWP";
                                    k += 2;
                                    if (size > 0){
                                        out << "   ";
                                        out << players[index].front();
                                        k += 4;
                                    }
                                }   else if (j == 10 && k == 0){
                                    out << "REV";
                                    k += 2;
                                    if (size > 0){
                                        out << "   ";
                                        out << players[index].front();
                                        k += 4;
                                    }   
                                }   else if ((j == 2 && k == 4) || (j == 8 && k ==2)){
                                            out <<'|';
                                }   else if ((j == 2 && k == 6) || (j == 3 && (k == 2 || k == 5 || k == 6)) || (j == 4 && (k >= 1 && k <=5)) || (j == 5 && (k >= 0 && k <=2))){
                                    out << '#';
                                }   else if ((j == 5 && (k == 5 || k == 6 || k == 7)) || (j == 6 && (k >= 3 && k <= 5)) || (j == 7 && (k == 0 || k == 4)) || (j == 8 && k == 0)){
                                    out << '#';
                                }   else {
                                    out << ' ';
                                } 
                            }   else if (i == 27){
                                    if (size > 1 && k == 0 && (j == 0 || j == 10)){
                                        auto playerIt = players[index].begin();
                                        playerIt++;
                                        k--;
                                        while (playerIt != players[index].end()){
                                            out << *playerIt;
                                            playerIt++;
                                            k++;
                                        }   
                                    }   else if ((j == 2 && k == 4) || (j == 8 && k ==2)){
                                            out <<'|';
                                }   else if ((j == 2 && k == 6) || (j == 3 && (k == 2 || k == 4 || k == 7)) || (j == 4 && (k == 3 || k == 7)) || (j == 5 && k == 3)){
                                    out << '#';
                                }   else if ((j == 5 && k == 5) || (j == 6 && (k == 0 || k == 2 || k == 6)) || (j == 7 && (k == 0 || k == 4))|| (j == 8 && k == 0)){
                                    out << '#';
                                }
                                    else {
                                    out << ' ';
                                }
                            }   else if (i == 28){
                                if ((j == 2 && k == 4) || (j == 8 && k ==2)){
                                    out <<'|';
                                }   else if ((j == 2 && k == 6) || (j == 3 && (k == 0 || k == 2 || (k>=4 && k <=7))) || (j == 4 && (k == 3 || k == 7)) || (j == 5 && k == 3)){
                                    out << '#';
                                }   else if ((j == 5 && (k == 5 || k == 6 || k == 7)) || (j == 6 && (k == 0 || k == 2 || k == 6)) || (j == 7 && (k == 0 || k == 5 || k == 7))){
                                    out << '#';
                                }
                                    else {
                                    out << ' ';
                                }
                            }   else if (i == 29){
                                if ((j == 2 && k == 4) || (j == 8 && k ==2)){
                                    out <<'|';
                                }   else if ((j == 2 && k == 6) || (j == 3 && (k == 0 || k == 2 || k == 4 || k == 7)) || (j == 4 && (k == 3 || k == 7)) || (j == 5 && k == 3)){
                                    out << '#';
                                }   else if ((j == 5 && k == 5) || (j == 6 && (k == 2 || k == 6)) || (j == 7 && (k == 0 || k == 6))){
                                    out << '#';
                                }
                                    else {
                                    out << ' ';
                                }
                            }   else if (i == 30){
                                if ((j == 0 || j == 10) && (k == 0)){
                                    out << "_______";
                                    k += 6;
                                }   else if ((j == 2 && k == 4) || (j == 8 && k ==2)){
                                    out <<'|';
                                }   else if ((j == 2 && (k == 6 || k == 7)) || (j == 3 && (k == 7 || k == 4 || (k >=0 && k <=2))) || (j == 4 && k == 3) || (j == 5 && (k >=0 && k <=2))){
                                    out << '#';
                                }   else if ((j == 5 && k == 5) || (j == 6 && (k<=5 && k >=3)) || (j == 7 && (k == 0 || k == 1 || k == 3|| k == 6))){
                                    out << '#';
                                }
                                    else {
                                    out << ' ';
                                }
                            }   else if (i == 31){
                                if (j > 1 && j < 9){
                                    if ((j == 2 && k == 4) || (j == 8 && k ==2)){
                                    out <<'|';
                                }   else if (j == 2 && k <= 4){
                                        out << ' ';
                                    }   else if (j == 8 && k >= 2){
                                        out << ' ';
                                    }   else {
                                        out << '_';
                                    }
                                }   else if ( j == 10 && k == 0){
                                    out << "NEEDLES";
                                    k+=6;
                                }   else if ( j == 0 && k == 0){
                                    auto property = dynamic_cast<AcademicBuilding&>(*(buildings[convert(i/5,j)]));
                                    int level = property.getImprovedLevel();
                                   
                                    for (int p = 0; p < level; p++){
                                        if (p == 0)k--;
                                        out << "I";
                                        k++;
                                    }
                                    if (level == 0) out << ' ';
                                }
                                   else {
                                    out << ' ';
                                } 
                            }   else if ( i > 31){
                                if ( i ==37 || i == 47){
                                    if (k ==0 && (j == 0 || j == 10)){
                                        out << "-------";
                                        k += 6;
                                    }   else {
                                        out << ' ';
                                    }
                                }  else if (i == 35 || i == 40 || i == 45 || i == 50){
                                    if (k ==0 && (j == 0 || j == 10)){
                                        out << "_______";
                                        k += 6;
                                    }   else {
                                        if (i == 50){
                                            out << '_';
                                        }   else {
                                            out << ' ';
                                        }
                                    }
                                }   else if (i == 36 || i == 46){
                                    if ((j == 0 || j == 10) && k == 0){
                                        auto property = dynamic_cast<AcademicBuilding&>(*(buildings[convert(i/5,j)]));
                                        int level = property.getImprovedLevel();
                                       
                                        for (int p = 0; p < level; p++){
                                            if (p == 0)k--;
                                            out << "I";
                                            k++;
                                        }
                                        if (level == 0) out << ' ';
                                        }   else {
                                            out << ' ';
                                        }
                                    }
                                    else if (i == 32){
                                    if (j == 0 && k == 0){
                                        out << "-------";
                                        k += 6;
                                    }   else if (j == 10 && k == 0){
                                        out << "HALL";
                                        k += 3;
                                        if (size > 0){
                                        out << "  ";
                                        out << players[index].front();
                                        k += 3;
                                    }
                                    }   else {
                                        out << ' ';
                                    }
                                }   else if (i == 33){
                                    if (j == 0 && k == 0){
                                        out << "CPH";
                                        k += 2;
                                        if (size > 0){
                                        out << "   ";
                                        out << players[index].front();
                                        k += 4;
                                    }
                                    }   else if (j == 10 && k == 0 && size > 1){
                                        auto playerIt = players[index].begin();
                                        playerIt++;
                                        k--;
                                        while (playerIt != players[index].end()){
                                            out << *playerIt;
                                            playerIt++;
                                            k++;
                                        } 
                                    }   else {
                                        out << ' ';
                                    }
                                }   else if (i == 34){
                                    if (j == 0 && k == 0 && size > 1){
                                       auto playerIt = players[index].begin();
                                        playerIt++;
                                        k--;
                                        while (playerIt != players[index].end()){
                                            out << *playerIt;
                                            playerIt++;
                                            k++;
                                        } 
                                    }   else {
                                        out << ' ';
                                    }
                                }  
                                    else {
                                    if ((i == 38 || i == 41 || i == 48)){
                                        if (j == 0 && k == 0){
                                            if (i == 38) out << "DWE";
                                            if (i == 41) out << "PAC";
                                            if (i == 48) out << "RCH";
                                            k += 2;
                                            if (size > 0){
                                                out << "   ";
                                                out << players[index].front();
                                                k += 4;
                                            }
                                        }   else if (j == 10 && k == 0){
                                            if (i == 38){
                                                out << "MC";
                                                k += 1;
                                            } 
                                            if (i == 48) {
                                                out << "DC";
                                                k += 1;
                                            }
                                            if (i == 41){
                                                out << "COOP";
                                                k += 3;
                                            }
                                            if (size > 0){
                                                if (i == 38 || i == 48){
                                                out << "    ";
                                                k += 5;
                                                }   else {
                                                    out << "  ";
                                                    k += 3;
                                                }
                                                out << players[index].front();  
                                            }
                                        }   else {
                                            out << ' ';
                                        }
                                        }  else if (i == 39 || i == 42 || i == 49){
                                            if (size > 1 && k == 0 && (j == 0 || j == 10)){
                                                auto playerIt = players[index].begin();
                                                playerIt++;
                                                k--;
                                                while (playerIt != players[index].end()){
                                                    out << *playerIt;
                                                    playerIt++;
                                                    k++;
                                                }   
                                            }   else {
                                                out << ' ';
                                            }
                                        }   else if (i == 51){
                                            if (j == 0 && k == 0){
                                                out << "DC Tims";
                                                k += 6;
                                            }   else if (j == 3 && k == 0){
                                                out << "NEEDLES";
                                                k += 6;
                                            }   else if (j == 5 && k == 0){
                                                out << "MKV";
                                                k += 2;
                                            }   else if (j == 6 && k == 0){
                                                out << "TUITION";
                                                k += 6;
                                            }   else if (j == 8 && k == 0){
                                                out << "SLC";
                                                k += 2;
                                            }   else if (j == 10 && k == 0){
                                                out << "COLLECT";
                                                k += 6;
                                            }   else {
                                                if (k == 0){
                                                    auto property = dynamic_cast<AcademicBuilding&>(*(buildings[convert(i/5,j)]));
                                                    int level = property.getImprovedLevel();
                                                    for (int p = 0; p < level; p++){
                                                        out << "I";
                                                        k++;
                                                    }
                                        
                                                }
                                                
                                                // add property here
                                                if (k == b.length-1){
                                                    out << '|';
                                                }   else {
                                                    out << ' ';
                                                }
                                            }
                                        }   else if (i == 52){
                                            if(k == 0 && j == 0){
                                                out << "Line";
                                                k += 3;
                                            }   else if (k == 0 && j == 3){
                                                out << "HALL";
                                                k += 3;
                                            }   else if (k == 0 && j == 10){
                                                out << "OSAP";
                                                k += 3;
                                            }   else if ((j == 1 || j == 2 || j == 4 || j == 7 || j == 9)&& k == 0){
                                                out << "-------";
                                                k += 6;
                                            }   else {
                                                if (k == b.length-1){
                                                    out << '|';
                                                }   else {
                                                    out << ' ';
                                                }
                                            }
                                        }   else if (i == 53){
                                            if (k == 0 && (j == 0 || j == 3 || j == 5||j == 6 || j == 8 || j == 10)){
                                                out << "      ";
                                                k += 5;
                                                if (size > 0){
                                                    out << players[index].front();
                                                    k += 1;
                                                }
                                            }   else if (k == 0 && j == 1){
                                                out << "HH";
                                                k += 1;
                                                if (size > 0){
                                                    out << "    ";
                                                    out << players[index].front();
                                                    k += 5;
                                                }
                                            }   else if (k == 0 && j == 2){
                                                out << "PAS";
                                                k += 2;
                                                if (size > 0){
                                                    out << "   ";
                                                    out << players[index].front();
                                                    k += 4;
                                                }
                                            }   else if (k == 0 && j == 4){
                                                out << "ECH";
                                                k += 2;
                                                if (size > 0){
                                                    out << "   ";
                                                    out << players[index].front();
                                                    k += 4;
                                                }
                                            }   else if (k == 0 && j == 7){
                                                out << "ML";
                                                k += 1;
                                                if (size > 0){
                                                    out << "    ";
                                                    out << players[index].front();
                                                    k += 5;
                                                }
                                            }   else if (k == 0 && j == 9){
                                                out << "AL";
                                                k += 1;
                                                if (size > 0){
                                                    out << "    ";
                                                    out << players[index].front();
                                                    k += 5;
                                                }
                                            }   else {
                                                if (k == b.length-1){
                                                    out << '|';
                                                }   else {
                                                    out << ' ';
                                                }
                                            }
                                        }   else if (i == 54){
                                            if (size > 1 && k == 0 ){
                                                auto playerIt = players[index].begin();
                                                playerIt++;
                                                k--;
                                                while (playerIt != players[index].end()){
                                                    out << *playerIt;
                                                    playerIt++;
                                                    k++;
                                                }   
                                            }   else {
                                                if (k == b.length-1){
                                                    out << '|';
                                                }   else {
                                                    out << ' ';
                                                }
                                            }
                                        }
                                           else {
                                            out << ' ';
                                        }
                                    }
                            } 
                              
                        }
                    }         
                }   
    }
     out << std::endl;
    }
    return out;
}


