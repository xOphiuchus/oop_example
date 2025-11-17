#pragma once
#include <vector>
#include <memory>
#include <string>
#include "BaseTask.hpp"

class TUI
{
public:
    static void displayTasks(const std::vector<std::unique_ptr<BaseTask>> &tasks);
    static void showHelp();
    static void showMessage(const std::string &message);
};
