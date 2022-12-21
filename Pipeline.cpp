#include <algorithm>
#include <iostream>
#include <numeric>
#include "Pipeline.hpp"

Pipeline::Pipeline(int mem_AT, int exe1, int exe2, std::queue<Command *> inp) : MAT(mem_AT), memory_blocked(false),
                                                                                input_blocked(false), tic_overall(0) {
    input = inp;
    cmd_amount = input.size();
    current_stage = 0;
    cmd_exe_time[Type1] = exe1;
    cmd_exe_time[Type2] = exe2;
    cmd_exe_time[Type3] = 1;
}

int Pipeline::check_time_per_stage() {
    return *std::max_element(tic_per_action.begin(), tic_per_action.end());
}

void Pipeline::fill_TPA() {
    tic_per_action[0] = (pipe[0] != nullptr) ? 1 : 0;

    if (pipe[1] != nullptr)
        tic_per_action[1] = (pipe[1]->get_operand_type(1) == REG) ? 1 : MAT;
    else tic_per_action[1] = 0;

    if (pipe[2] != nullptr)
        tic_per_action[2] = (pipe[2]->get_operand_type(2) == REG) ? 1 : MAT;
    else tic_per_action[2] = 0;

    if (pipe[3] != nullptr)
        tic_per_action[3] = cmd_exe_time[pipe[3]->get_type()];
    else tic_per_action[3] = 0;

    if (pipe[4] != nullptr)
        tic_per_action[4] = tic_per_action[2];
    else tic_per_action[4] = 0;
}

void Pipeline::check_input_block() {
    for (auto cmd: pipe) {
        if (cmd != nullptr) {
            if (cmd->get_type() == Type3) input_blocked = true;
        }
    }
}

void Pipeline::check_memory_block() {
    if (pipe[0] != nullptr && pipe[1] != nullptr && pipe[2] != nullptr && pipe[4] != nullptr) {
        memory_blocked = true;
    } else {
        memory_blocked = false;
    }
}

void Pipeline::command_exit(Command *cmd) {
    tic_per_cmd.push_back(cmd->get_tics());
    if (cmd->get_type() == Type3) input_blocked = false;
}

void Pipeline::start() {
    while (pipeline_is_busy() || !input.empty()) {
        current_stage++;
        check_input_block();
        check_memory_block();
        move_stage();
        fill_TPA();
        print_stage();
        clock();
    }
    finish();
}


bool Pipeline::pipeline_is_busy() {
    return std::ranges::any_of(pipe.begin(), pipe.end(), [](Command *i) { return i != nullptr; });
}

void Pipeline::move_stage() {
    for (int i = pipe.size() - 1; i >= 0; i--) {
        if (i == pipe.size() - 1 && pipe[i] != nullptr) {
            command_exit(pipe[i]);
            pipe[i] = nullptr;
            continue;
        } else if (memory_blocked && i == 0) continue;
        if (pipe[i] != nullptr && pipe[i + 1] == nullptr) {
            pipe[i + 1] = pipe[i];
            pipe[i] = nullptr;
        }
    }
    if (input_blocked || memory_blocked || pipe[0] == nullptr) return;

    pipe[0] = input.front();
    input.pop();
}

void Pipeline::clock() {
    for (auto i = 0; i < check_time_per_stage(); i++) {
        for (auto cmd: pipe) {
            if (cmd != nullptr) cmd->clock();
        }
        tic_overall++;
    }
}

void Pipeline::print_stage() {
    std::cout << "Stage " << current_stage << std::endl;
    for (int i = 0; i < pipe.size(); i++) {
        std::cout << stages[i] << '\t';
        if (pipe[i] != nullptr) {
            std::cout << "Command Type " << pipe[i]->get_type() << std::endl;
        }
    }
}

void Pipeline::finish() {
    std::cout <<"\n\n\n";
    std::cout << "Pipeline ended its work in " << tic_overall << " tics" << std::endl;

    double sum_time = std::accumulate(tic_per_cmd.begin(), tic_per_cmd.end(), 0);
    double average_cmd_time = sum_time / cmd_amount;
    std::cout << "Average execution time of command is " << average_cmd_time << " tics" << std::endl;
}
