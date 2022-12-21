#ifndef COMPARCH_COURSEWORK_RANDGEN_HPP
#define COMPARCH_COURSEWORK_RANDGEN_HPP

#include <queue>
#include <random>
#include "Command.hpp"

class RandGen {
public:
    RandGen() = default;

    std::queue<Command *> generate_cmd_q(double p_reg, double p_type, int amount);

};


#endif //COMPARCH_COURSEWORK_RANDGEN_HPP
