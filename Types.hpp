//
// Created by Xialin He on 2021/6/28.
//

#ifndef RISC_V_TYPES_HPP
#define RISC_V_TYPES_HPP

enum BIG_TYPE{
    U,J,I,B,S,R
};
enum type{
    LUI,AUIPC,
    JAL,
    LB,LH,LW,LBU,LHU,
    JALR,ADDI,SLTI,SLTIU,XORI,ORI,ANDI,
    BEQ,BNE,BLT,BGE,BLTU,BGEU,
    SB,SH,SW,
    SLLI,SRLI,SRAI,ADD,SUB,SLL,SLT,SLTU,XOR,SRL,SRA,OR,AND,
    NOP

};
#endif //RISC_V_TYPES_HPP
