#ifndef COMPARCH_COURSEWORK_COMMAND_HPP
#define COMPARCH_COURSEWORK_COMMAND_HPP

enum OpType {
    REG,
    MEM
};

enum CMDType {
    Type1,
    Type2,
    Type3
};


class Command {
public:
    Command(CMDType _type, OpType op1, OpType op2);

    CMDType get_type() const;

    void clock();

    OpType get_operand_type(int number);

    int get_tics();

private:
    CMDType cmd_type;

    // operands types
    OpType op1_type, op2_type;
    int tic_overall;
};


#endif //COMPARCH_COURSEWORK_COMMAND_HPP
