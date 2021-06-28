//
// Created by Xialin He on 2021/6/28.
//
#include <iostream>
#include "Types.hpp"
#include "Simulator.hpp"
Simulator Si;
using namespace std;
int main(){
    unsigned int x;
    cin >> hex >> x;
    Si.gettokentype(x);
    return 0;
}

