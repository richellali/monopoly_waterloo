#include "roll.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

int rollnum1() {
    for (int n = 0; n < 2; n++) {
      srand(time(NULL));
      for (int i = 0; i <6; i++) {
          int result = rand()% 6+1;
          std::cout << "Your first die rolled " << result << std::endl;
          return result;
        }
    }
     return 0;     
}

int rollnum2() {
    for (int n = 0; n < 2; n++) {
      //srand(time(NULL));
      for (int i = 0; i <6; i++) {
          int result = rand()% 6+1;
          std::cout << "Your second die rolled " << result << std::endl;
          return result;
        }
    }
     return 0;     
}

int rollnum3() {
    for (int n = 0; n < 2; n++) {
      srand(time(NULL));
      for (int i = 0; i <6; i++) {
          int result = rand()% 6+1;
          std::cout << "Your third die rolled " << result << std::endl;
          return result;
        }
    }
     return 0;     
}

int rollnum4() {
    for (int n = 0; n < 2; n++) {
      for (int i = 0; i <6; i++) {
          int result = rand()% 6+1;
          std::cout << "Your fourth die rolled " << result << std::endl;
          return result;
        }
    }
     return 0;     
}

int rollnum5() {
    for (int n = 0; n < 2; n++) {
      srand(time(NULL));
      for (int i = 0; i <6; i++) {
          int result = rand()% 6+1;
          std::cout << "Your fifth die rolled " << result << std::endl;
          return result;
        }
    }
     return 0;     
}

int rollnum6() {
    for (int n = 0; n < 2; n++) {
      for (int i = 0; i <6; i++) {
          int result = rand()% 6+1;
          std::cout << "Your sixth die rolled " << result << std::endl;
          return result;
        }
    }
     return 0;     
}

