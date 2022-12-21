#include "RandGen.hpp"
#include "Pipeline.hpp"

int main()
{
    RandGen rg;
    auto cmd_queue = rg.generate_cmd_q(0.85, 0.9, 1000);
    Pipeline pipe1(2, 1, 4, cmd_queue);
    pipe1.start();
    return 0;
}