#include "Command.hpp"

Command::Command(CMDType _type, OpType op1, OpType op2) : cmd_type(_type), tic_overall(0), op1_type(op1),
                                                          op2_type(op2) {}

void Command::clock() {
    tic_overall++;
}

CMDType Command::get_type() const {
    return cmd_type;
}

OpType Command::get_operand_type(int number) {
    if (number == 1) return op1_type;
    return op2_type;
}

int Command::get_tics() {
    return tic_overall;
}
