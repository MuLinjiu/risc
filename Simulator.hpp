//
// Created by Xialin He on 2021/6/28.
//

#ifndef RISC_V_SIMULATOR_HPP
#define RISC_V_SIMULATOR_HPP
#include "Types.hpp"
#include <cmath>
unsigned char memory[1000000];
unsigned int a[100];
class Simulator{
public:
    int sext(int length,int as){
        as = as | (~((1 << length) - 1));
        return as;
    }
    int x[32];
    unsigned int pc = 0;
    Simulator() {
        x[0] = 0;
    }
    type funct3(unsigned int x1,unsigned int opt){
        if(opt == 99) {
            switch (x1) {
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
            switch (x1) {
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
            switch(x1){
                case 0:
                    return SB;
                case 1:
                    return SH;
                case 2:
                    return SW;
                default: throw("d");
            }
        }else if(opt == 19){
            switch (x1) {
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
    type funct7(unsigned int x1,unsigned int y,unsigned int opt){
        if(opt == 19){
            if(x1 == 0)return ADDI;
            else if(x1 == 2)return SLTI;
            else if(x1 == 3)return SLTIU;
            else if(x1 == 4)return XORI;
            else if(x1 == 6)return ORI;
            else if(x1 == 7)return ANDI;
            else if(x1 == 1 && y == 0)return SLLI;
            else if(x1 == 5 && y == 0)return SRLI;
            else if(x1 == 5 && y == 32)return SRAI;
        }else if(opt == 51){
            if(x1 == 0 && y == 0)return ADD;
            else if(x1 == 0 && y == 32)return SUB;
            else if(x1 == 1 && y == 0)return SLL;
            else if(x1 == 2 && y == 0)return SLT;
            else if(x1 == 3 && y == 0)return SLTU;
            else if(x1 == 4 && y == 0)return XOR;
            else if(x1 == 5 && y == 0)return SRL;
            else if(x1 == 5 && y == 32)return SRA;
            else if(x1 == 6 && y == 0)return OR;
            else if(x1 == 7 && y == 0)return AND;
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
    BIG_TYPE gettokenbigtype(unsigned int x_){
        unsigned int y = x_ & 127;
        unsigned int x1 = x_ << 12;
        x1 &= 7;
        if(y == 0b0110111)return U;
        if(y == 0b0010111)return U;
        if(y == 0b1101111)return J;
        if(y == 0b1100011)return B;
        if(y == 0b0000011)return I;
        if(y == 0b1100111)return I;
        if(y == 0b0100011)return S;
        if(y == 0b0110011)return R;
        if(y == 0b0010011){
            if(x1 == 1 || x1 == 5)return R;
            else return I;
        }
    }
    void IF(){
        //unsigned int command = (memory[pc] << 24) + (memory[pc + 1] << 16) + (memory[pc + 2] << 8) + memory[pc + 3];
        unsigned int command = (memory[pc + 3] << 24) + (memory[pc + 2] << 16) + (memory[pc + 1] << 8) + memory[pc];
        ID(command);
        pc += 4;
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
                ans = x[rs1] << x[rs2];
            }else if(t == SLT){
                ans = (x[rs1] < x[rs2]);
            }else if(t == SLTU){
                ans = ((unsigned int)x[rs1] < (unsigned int)x[rs2]);
            }else if(t == XOR){
                ans = x[rs1] ^ x[rs2];
            }else if(t == SRL){
                ans = ((unsigned int)x[rs1]) >> (unsigned int)x[rs2];
            }else if(t == SRA){
                ans = x[rs1] >> x[rs2];
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
            imm110 = imm110 | (~((1 << 12) - 1));
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
                //x[rd]=t_;
                MEM(I,t_,rd);
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
        }else if(BT == S){
            unsigned int rs1 = (command >> 15) & 31;
            unsigned int rs2 = (command >> 20) & 31;
            unsigned int imm115 = command >> 25;
            unsigned int imm40 = (command >> 7) & 31;
            unsigned int imm = (imm115 << 5) + imm40;
            imm = sext(12,imm);
            type t = gettokentype(command);
            if(t == SB){
                unsigned offset = x[rs1] + imm;
                //memory[offset] = (x[rs2] & ((1 << 8) - 1));
            }else if(t == SH){
                unsigned offset = x[rs1] + imm;
                //memory[offset] = (x[rs2] & ((1 << 16) - 1));
            }else if(t == SW){
                unsigned offset = x[rs1] + imm;
                //memory[offset] = x[rs2];
            }
        }else if(BT == B){
            unsigned int rs1 = (command >> 15) & 31;
            unsigned int rs2 = (command >> 20) & 31;
            unsigned int imm = ((command >> 31) << 12) + (((command >> 7) & 1) << 11) + (((command >> 25) & 63) << 5) + (((command >> 8) & 15) << 1);
            imm = sext(13,imm);
            type t = gettokentype(command);
            if(t == BEQ){
                if(rs1 == rs2)pc += imm;
            }else if(t == BNE){
                if(rs1 != rs2)pc += imm;
            }else if(t == BLT){
                if(rs1 < rs2)pc += imm;
            }else if(t == BGE){
                if(rs1 >= rs2)pc += imm;
            }else if(t == BLTU){
                if((unsigned)rs1 < (unsigned)rs2)pc += imm;
            }else if(t == BGEU){
                if((unsigned)rs1 >= (unsigned)rs2)pc += imm;
            }
        }
    }
    void MEM(BIG_TYPE BT,unsigned int ans, unsigned int offset){

    }

};

#endif //RISC_V_SIMULATOR_HPP
