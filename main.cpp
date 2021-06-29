//
// Created by Xialin He on 2021/6/28.
//
#include <iostream>
#include <sstream>
#include "Types.hpp"
#include "Simulator.hpp"
Simulator Si;
using namespace std;
int memorypointer = 0,pos;
string s;
void INPUT(){
    while(getline(cin,s)){
        if(s[0] == '@') {
            s = s.substr(1);
            stringstream stringstream1(s);
            stringstream1 >> hex >> pos;
        }
        else {
            stringstream stringstream2(s);
            while (stringstream2 >> a[0] >> a[1] >> a[2] >> a[3]) {
                //reverse(a, a + 4);
                for (int i = 0; i < 4; i++)memory[pos++] = a[i];
            }
        }
    }
}
int main(){

    return 0;
}

