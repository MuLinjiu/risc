//
// Created by Xialin He on 2021/6/28.
//

#ifndef RISC_V_SIMULATOR_HPP
#define RISC_V_SIMULATOR_HPP
#include "Types.hpp"

class Simulator{
public:
    Simulator() = default;
    type funct3(unsigned int x,unsigned int opt){
        if(opt == 99) {
            switch (x) {
                case 0:
                    return BEQ;
                case 1:
                    return BNE;
                case 4:
                    return BLT;
                case 5:
                    return BGE;
                case 6:
                    return BLTU;
                case 7:
                    return BGEU;
                default: throw("e");
            }
        }else if(opt == 3){
            switch (x) {
                case 0:
                    return LB;
                case 1:
                    return LH;
                case 2:
                    return LW;
                case 4:
                    return LBU;
                case 5:
                    return LHU;
                default:throw("e");
            }
        }else if(opt == 35){
            switch(x){
                case 0:
                    return SB;
                case 1:
                    return SH;
                case 2:
                    return SW;
                default: throw("d");
            }
        }else if(opt == 19){
            switch (x) {
                case 0:
                    return ADDI;
                case 2:
                    return SLTI;
                case 3:
                    return SLTIU;
                case 4:
                    return XORI;
                case 6:
                    return ORI;
                case 7:
                    return ANDI;
                default:throw("g");
            }
        }
    }
    type funct7(unsigned int x,unsigned int y,unsigned int opt){
        if(opt == 19){
            if(x == 0)return ADDI;
            else if(x == 2)return SLTI;
            else if(x == 3)return SLTIU;
            else if(x == 4)return XORI;
            else if(x == 6)return ORI;
            else if(x == 7)return ANDI;
            else if(x == 1 && y == 0)return SLLI;
            else if(x == 5 && y == 0)return SRLI;
            else if(x == 5 && y == 32)return SRAI;
        }else if(opt == 51){
            if(x == 0 && y == 0)return ADD;
            else if(x == 0 && y == 32)return SUB;
            else if(x == 1 && y == 0)return SLL;
            else if(x == 2 && y == 0)return SLT;
            else if(x == 3 && y == 0)return SLTU;
            else if(x == 4 && y == 0)return XOR;
            else if(x == 5 && y == 0)return SRL;
            else if(x == 5 && y == 32)return SRA;
            else if(x == 6 && y == 0)return OR;
            else if(x == 7 && y == 0)return AND;
        }
    }
    type gettokentype(unsigned int x){
        unsigned int case1 = x & 127;
        unsigned int x1 = x;
        unsigned int x2 = x;
        x1 = x1 >> 12;
        x1 = x1 & 7;
        x2 = x2 >> 25;
        switch (case1) {
            case 55: return LUI;
            case 23: return AUIPC;
            case 111: return JAL;
            case 103: return JALR;
            case 99: {
                return funct3(x1,case1);
            }
            case 3:{//0000011
                return funct3(x1,case1);
            }
            case 35:{//0100011
                return funct3(x1,case1);
            }
            case 19:{//0010011
                return funct7(x1,x2,case1);
            }
            case 51:{//0110011
                return funct7(x1,x2,case1);
            }
            default:throw ("e");
        }
    }
};

#endif //RISC_V_SIMULATOR_HPP
