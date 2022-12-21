#include "RandGen.hpp"

std::queue<Command *> RandGen::generate_cmd_q(double p_reg, double p_type, int amount) {
    std::queue<Command *> res;

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 100); // define the range

    int p_type1 = p_type * 100;
    int p_type2 = (100 - p_type1) / 2 + p_type1;

    int reg_type = 100 * p_reg;

    for (auto i = 0; i < amount; i++) {
        int type_det, op1_det, op2_det;
        CMDType type;
        OpType op1, op2;

        // define type of command
        type_det = distr(gen);
        if (type_det <= p_type1) {
            type = Type1;
        } else if (type_det <= p_type2 && type_det > p_type1) {
            type = Type2;
        } else {
            type = Type3;
        }

        //define operators
        op1_det = distr(gen);
        if (op1_det <= reg_type) {
            op1 = REG;
        } else {
            op1 = MEM;
        }

        op2_det = distr(gen);
        if (op2_det <= reg_type) {
            op2 = REG;
        } else {
            op2 = MEM;
        }

        auto temp = new Command(type, op1, op2);
        res.push(temp);
    }
    return res;
}
