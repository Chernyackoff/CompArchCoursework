#include "RandGen.hpp"
#include "Pipeline.hpp"

int main()
{
    RandGen rg;

    // аргументы - вероятность регистрового обращения, вероятность команды 1го типа, кол-во команд
    auto cmd_queue = rg.generate_cmd_q(0.7, 0.7, 1000);

    // аргументы - время обращения к памяти, время выполнения команды 1го типа, 2го типа, очередь команд
    Pipeline pipe1(5, 2, 8, cmd_queue);
    pipe1.start();
    return 0;
}