#ifndef COMPARCH_COURSEWORK_PIPELINE_HPP
#define COMPARCH_COURSEWORK_PIPELINE_HPP

#include <string>
#include <array>
#include <vector>
#include <queue>
#include <map>
#include "Command.hpp"

std::map<int, std::string> stages = {{0, "IF&ID"}, {1, "OP1"}, {2, "OP2"}, {3, "EXE"}, {4, "WB"}};

class Pipeline {
public:
    Pipeline(int mem_AT, int ex1, int ex2, std::queue<Command*> inp);

    void start();

protected:
    // Get maximum time per action on a current stage
    int check_time_per_stage();

    // Fill Time per Action array with tics required by command
    void fill_TPA();

    // Fill pipe with commands or move 'em to the naxt stage
    void move_stage();

    // execute ~~order 66~~ stage
    void clock();

    void check_input_block();

    void check_memory_block();

    void command_exit(Command *cmd);

    // check if there is a command in pipeline
    bool pipeline_is_busy();

    void print_stage();

    void finish();

private:

    // Pipeline parameters
    const int MAT;                          // memory access time

    std::map<CMDType, int> cmd_exe_time;   // Command execution time map

    // Pipeline states
    bool memory_blocked;
    bool input_blocked;

    // Pipeline input and internals
    std::queue<Command*> input;
    std::vector<int> tic_per_cmd;
    std::vector<int> tic_theoretical;

    std::array<Command *, 5> pipe;
    std::array<int, 5> tic_per_action;

    int tic_overall;
    int current_stage;
    int cmd_amount;


};


#endif //COMPARCH_COURSEWORK_PIPELINE_HPP
