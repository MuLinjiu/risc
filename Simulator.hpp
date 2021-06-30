//
// Created by Xialin He on 2021/6/28.
//

#ifndef RISC_V_SIMULATOR_HPP
#define RISC_V_SIMULATOR_HPP
#include<iostream>
#include "Types.hpp"
#include <cmath>

using namespace std;
unsigned char memory[1000000];
unsigned int a[100];
class Simulator{
public:
    int sext(int n,unsigned int x_){
//        as = as | (~((1 << length) - 1));
//        return as;
        if (x_ & (1u << (n - 1))){
            return x_ - (1u << n);
        } else return x_;
    }
    int x[32];
    unsigned int pc = 0;
    Simulator() {
        x[0] = 0;
        pc = 0;
    }
    type funct3(unsigned int x1,unsigned int opt){
        if(opt == 99) {
            switch (x1) {
                case 0:
                    //printf("BEQ");
                    return BEQ;
                case 1:
                    //printf("BNE");
                    return BNE;
                case 4:
                    //printf("BLT");
                    return BLT;
                case 5:
                    //printf("BGE");
                    return BGE;
                case 6:
                    //printf("BLTU");
                    return BLTU;
                case 7:
                    //printf("BGEU");
                    return BGEU;
                default: throw("e");
            }
        }else if(opt == 3){
            switch (x1) {
                case 0:
                    //printf("LB");
                    return LB;
                case 1:
                    //printf("LH");
                    return LH;
                case 2:
                    //printf("LW");
                    return LW;
                case 4:
                    //printf("LBU");
                    return LBU;
                case 5:
                    //printf("LHU");
                    return LHU;
                default:throw("e");
            }
        }else if(opt == 35){
            switch(x1){
                case 0:
                    //printf("SB");
                    return SB;
                case 1:
                    //printf("SH");
                    return SH;
                case 2:
                    //printf("SW");
                    return SW;
                default: throw("d");
            }
        }else if(opt == 19){
            switch (x1) {
                case 0:
                    //printf("ADDI");
                    return ADDI;
                case 2:
                    //printf("SLTI");
                    return SLTI;
                case 3:
                    //printf("SLTIU");
                    return SLTIU;
                case 4:
                    //printf("XORI");
                    return XORI;
                case 6:
                    //printf("ORI");
                    return ORI;
                case 7:
                    //printf("ANDI");
                    return ANDI;
                default:throw("g");
            }
        }
    }
    type funct7(unsigned int x1,unsigned int y,unsigned int opt){
        if(opt == 19){
            if(x1 == 0){
                //printf("ADDI");
                return ADDI;
            }
            else if(x1 == 2){
                //printf("ALTI");
                return SLTI;
            }
            else if(x1 == 3){
                //printf("SLTIU");
                return SLTIU;
            }
            else if(x1 == 4){
                //printf("XORI");
                return XORI;
            }
            else if(x1 == 6){
                //printf("ORI");
                return ORI;
            }
            else if(x1 == 7){
                //printf("ANDI");
                return ANDI;
            }
            else if(x1 == 1 && y == 0){
                //printf("SLLI");
                return SLLI;
            }
            else if(x1 == 5 && y == 0){
                //printf("SRLI");
                return SRLI;
            }
            else if(x1 == 5 && y == 32){
                //printf("SRAI");
                return SRAI;
            }
        }else if(opt == 51){
            if(x1 == 0 && y == 0){
                //printf("ADD");
                return ADD;
            }
            else if(x1 == 0 && y == 32){
                //printf("SUB");
                return SUB;
            }
            else if(x1 == 1 && y == 0){
                //printf("SLL");
                return SLL;
            }
            else if(x1 == 2 && y == 0){
                //printf("SLT");
                return SLT;
            }
            else if(x1 == 3 && y == 0){
                //printf("SLTU");
                return SLTU;
            }
            else if(x1 == 4 && y == 0){
                //printf("XOR");
                return XOR;
            }
            else if(x1 == 5 && y == 0){
                //printf("SRL");
                return SRL;
            }
            else if(x1 == 5 && y == 32){
                //printf("SRA");
                return SRA;
            }
            else if(x1 == 6 && y == 0){
                //printf("OR");
                return OR;
            }
            else if(x1 == 7 && y == 0){
                //printf("AND");
                return AND;
            }
        }
    }
    type gettokentype(unsigned int x_){
        unsigned int case1 = x_ & 127;
        unsigned int x1 = x_;
        unsigned int x2 = x_;
        x1 = x1 >> 12;
        x1 = x1 & 7;
        x2 = x2 >> 25;
        switch (case1) {
            case 55: {
                //printf("LUI");
                return LUI;
            }
            case 23: {
                //printf("AUIPC");
                return AUIPC;
            }
            case 111: {
                //printf("JAL");
                return JAL;
            }
            case 103: {
                //printf("JALR");
                return JALR;
            }
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
    BIG_TYPE gettokenbigtype(unsigned int x_){
        unsigned int y = x_ & 127;
        unsigned int x1 = x_ << 12;
        x1 &= 7;
        if(y == 0b0110111){
            ////printf(" U ");
            return U;
        }
        if(y == 0b0010111){
            ////printf(" U ");
            return U;
        }
        if(y == 0b1101111){
            ////printf(" J ");
            return J;
        }
        if(y == 0b1100011){
            ////printf(" B ");
            return B;
        }
        if(y == 0b0000011){
            ////printf("  ");
            return I;
        }
        if(y == 0b1100111){
            ////printf(" I ");
            return I;
        }
        if(y == 0b0100011){
            ////printf(" S ");
            return S;
        }
        if(y == 0b0110011){
            ////printf(" R ");
            return R;
        }
        if(y == 0b0010011){
            if(x1 == 1 || x1 == 5){
                ////printf(" R ");
                return R;
            }
            else {
                ////printf(" I ");
                return I;
            }
        }
    }
    bool IF(){
        //unsigned int command = (memory[pc] << 24) + (memory[pc + 1] << 16) + (memory[pc + 2] << 8) + memory[pc + 3];
        unsigned int command = (memory[pc + 3] << 24) + (memory[pc + 2] << 16) + (memory[pc + 1] << 8) + memory[pc];
        if(command == 0x0ff00513){
            printf("%u",(x[10] & 255));
            return false;
        }
        ID(command);
        pc += 4;
        ////printf("%u\t%u\t",command,pc);
        //cout << (unsigned)x[12] << "\t" << (unsigned)x[11] <<endl;
        return true;
    }
    void ID(unsigned int x_){
        BIG_TYPE BT = gettokenbigtype(x_);
        EX(BT,x_);
    }
    void EX(BIG_TYPE BT,unsigned int command){
        if(BT == R){
            unsigned int rd = (command >> 7) & 31;
            unsigned int rs1 = (command >> 15) & 31;
            unsigned int rs2 = (command >> 20) & 31;
            type t = gettokentype(command);
            int ans = 0;
            if(t == ADD){
                ans = x[rs1] + x[rs2];
            }else if(t == SUB){
                ans = x[rs1] - x[rs2];
            }else if(t == SLL){
                ans = x[rs1] << (x[rs2] & 0b11111);
            }else if(t == SLT){
                ans = (x[rs1] < x[rs2]);
            }else if(t == SLTU){
                ans = ((unsigned int)x[rs1] < (unsigned int)x[rs2]);
            }else if(t == XOR){
                ans = x[rs1] ^ x[rs2];
            }else if(t == SRL){
                ans = ((unsigned)x[rs1]) >> (unsigned int)(x[rs2] & 0b11111);
            }else if(t == SRA){
                ans = x[rs1] >> (x[rs2] & 0b11111);
            }else if(t == OR){
                ans = x[rs1] | x[rs2];
            }else if(t == AND){
                ans = x[rs1] & x[rs2];
            }
            MEM(R,ans,rd);
    }else if(BT == I){
            unsigned int rd = (command >> 7) & 31;
            unsigned int rs1 = (command >> 15) & 31;
            unsigned int imm110 = command >> 20;
            int ans = 0;
            imm110 = sext(12,imm110);
            type t = gettokentype(command);
            if(t == LB){
                unsigned int buffer =  x[rs1] + imm110;
                ans = memory[buffer];
                ans = sext(8,ans);
                //x[rd]=ans;
                MEM(I,ans,rd);
            }else if(t == JALR){
                unsigned int t_ = pc + 4;
                pc = (x[rs1] + imm110) & (~1);
                pc -= 4;
                //x[rd]=t_;
                if(rd)MEM(I,t_,rd);
            }else if(t == LH){
                unsigned int pos = x[rs1] + imm110;
                unsigned int tmp = (memory[pos + 1] << 8) + memory[pos];
                tmp = sext(16,tmp);
                //x[rd] = tmp;
                MEM(I,tmp,rd);
            }else if(t == LW){
                unsigned int pos = x[rs1] + imm110;
                unsigned int tmp = (memory[pos + 3] << 24) + (memory[pos + 2] << 16) + (memory[pos + 1] << 8) + memory[pos];
                //x[rd]=tmp;
                MEM(I,tmp,rd);
            }else if(t == LBU){
                unsigned int buffer =  (unsigned)x[rs1] + (unsigned)imm110;
                ans = memory[buffer];
                //x[rd] = ans;
                MEM(I,ans,rd);
            }else if(t == LHU){
                unsigned int pos = (unsigned)x[rs1] + imm110;
                unsigned int tmp = (memory[pos + 1] << 8) + memory[pos];
                //x[rd]=tmp;
                MEM(I,tmp,rd);
            }else if(t == ADDI){
                ans = x[rs1] + imm110;
                //x[rd]=ans;
                MEM(I,ans,rd);
            }else if(t == SLTI){
                ans = (x[rs1] < imm110);
                //x[rd]=ans;
                MEM(I,ans,rd);
            }else if(t == SLTIU){
                ans = ((unsigned)x[rs1] < (unsigned)imm110);
                //x[rd]=ans;
                MEM(I,ans,rd);
            }else if(t == XORI){
                ans = x[rs1] ^ imm110;
                MEM(I,ans,rd);
                //
            }else if(t == ANDI){
                ans = x[rs1] & imm110;
                MEM(I,ans,rd);
                //
            }
            else if(t == SLLI){
                unsigned int rs2 = (command >> 20) & 31;
                ans = x[rs1] << rs2;
                ////printf(" %u\n",rs2);
                MEM(R,ans,rd);
            }else if(t == SRLI){
                unsigned int rs2 = (command >> 20) & 31;
                ans = (unsigned)x[rs1] >> (unsigned)rs2;
                MEM(R,ans,rd);
            }else if(t == SRAI){
                unsigned int rs2 = (command >> 20) & 31;
                ans = x[rs1] >> rs2;
                MEM(R,ans,rd);
            }
        }else if(BT == S){
            unsigned int rs1 = (command >> 15) & 31;
            unsigned int rs2 = (command >> 20) & 31;
            unsigned int imm115 = command >> 25;
            unsigned int imm40 = (command >> 7) & 31;
            unsigned int imm = (imm115 << 5) + imm40;
            imm = sext(12,imm);
            type t = gettokentype(command);
            if(t == SB){
                unsigned int offset = x[rs1] + imm;
                //memory[offset] = (x[rs2] & ((1 << 8) - 1));
                MEM(S,(x[rs2] & ((1 << 8) - 1)),offset,1);
            }else if(t == SH){
                unsigned int offset = x[rs1] + imm;
                //memory[offset] = (x[rs2] & ((1 << 16) - 1));
                MEM(S,(x[rs2] & ((1 << 16) - 1)),offset,2);
            }else if(t == SW){
                unsigned int offset = x[rs1] + imm;
                //memory[offset] = x[rs2];
                MEM(S,x[rs2],offset,4);
            }
        }else if(BT == B){
            unsigned int rs1 = (command >> 15) & 31;
            unsigned int rs2 = (command >> 20) & 31;
            unsigned int imm = ((command >> 31) << 12) + (((command >> 7) & 1) << 11) + (((command >> 25) & 63) << 5) + (((command >> 8) & 15) << 1);
            imm = sext(13,imm);
            type t = gettokentype(command);
            if(t == BEQ){
                if(x[rs1] == x[rs2])pc += imm - 4;
            }else if(t == BNE){
                if(x[rs1] != x[rs2])pc += imm - 4;

            }else if(t == BLT){
                if(x[rs1] < x[rs2])pc += imm - 4;
            }else if(t == BGE){
                if(x[rs1] >= x[rs2])pc += imm - 4;
            }else if(t == BLTU){
                if((unsigned)x[rs1] < (unsigned)x[rs2]){
                    pc += imm - 4;
                }
            }else if(t == BGEU){
                if((unsigned)x[rs1] >= (unsigned)x[rs2])pc += imm - 4;
            }
            MEM(B,0,0);
        }else if(BT == U){
            unsigned int rd = (command >> 7) & 31;
            unsigned int imm3112 = (command >> 12) << 12;
            type t = gettokentype(command);
            unsigned int ans = 0;
            if(t == AUIPC){
                ans = pc + imm3112;
                //x[rd] = ans;
            }else if(t == LUI){
                ans = imm3112;
                //x[rd] = ans;
            }
            MEM(U,ans,rd);
        }else if (BT == J){
            unsigned int imm = ((command >> 31) << 20 ) + (((command >> 12) & 255) << 12) + (((command >> 20) & 1) << 11) + (((command >> 21) & 1023) << 1);
            unsigned int rd = (command >> 7) & 31;
            imm = sext(21,imm);
            unsigned int ans = pc + 4;
            pc += imm - 4;
            //x[rd] = ans;
            if(rd)MEM(J,ans,rd);
        }
    }
    void MEM(BIG_TYPE BT,unsigned int ans, unsigned int offset,int len = 0){
        if(BT == R)WB(BT,ans,offset);
        else if(BT == I)WB(BT,ans,offset);
        else if(BT == S){
            memory[offset] = ans & 255;
            if(len > 1)memory[offset + 1] = (ans >> 8) & 255;
            if(len > 2)memory[offset + 2] = (ans >> 16) & 255;
            if(len > 2)memory[offset + 3] = (ans >> 24) & 255;
            WB(BT,ans,offset);
        }
        else if(BT == B)WB(BT,ans,offset);
        else if(BT == U)WB(BT,ans,offset);
        else if(BT == J)WB(BT,ans,offset);
    }
    void WB(BIG_TYPE BT,unsigned int ans, unsigned int offset){
        if(BT == S || BT == B)return;
        ////printf(" %d \n",x[offset]);
        if(BT == R)x[offset] = ans;
        else if(BT == I)x[offset] = ans;
        else if(BT == U)x[offset] = ans;
        else if(BT == J)x[offset] = ans;
    }
    void RUN(){
        while(IF()){}
    }
};

#endif //RISC_V_SIMULATOR_HPP
