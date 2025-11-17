#include "TUI.hpp"
#include <iostream>
#include <iomanip>

void TUI::displayTasks(const std::vector<std::unique_ptr<BaseTask>> &tasks)
{
    std::cout << "\n=== Task List ===\n"
              << std::endl;

    if (tasks.empty())
    {
        std::cout << "No tasks. All clear!" << std::endl;
    }
    else
    {
        for (const auto &task : tasks)
        {
            task->display();
        }
        std::cout << "\nTotal tasks: " << tasks.size() << std::endl;
    }
    std::cout << "\n===============\n"
              << std::endl;
}

void TUI::showMessage(const std::string &message)
{
    std::cout << ">>> " << message << std::endl;
}

void TUI::showHelp()
{
    std::cout << "\nTask Manager Commands:\n"
              << "--------------------\n"
              << std::setw(25) << std::left << "list" << "Show all tasks\n"
              << std::setw(25) << std::left << "add \"title\" \"desc\"" << "Add a new task\n"
              << std::setw(25) << std::left << "done <id>" << "Mark task as complete\n"
              << std::setw(25) << std::left << "delete <id>" << "Remove a task\n"
              << std::setw(25) << std::left << "clear" << "Remove completed tasks\n"
              << std::setw(25) << std::left << "help" << "Show this help menu\n"
              << "--------------------\n"
              << std::endl;
}
