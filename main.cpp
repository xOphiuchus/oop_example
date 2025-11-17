#include <iostream>
#include <string>
#include <stdexcept>
#include "TaskList.hpp"
#include "TUI.hpp"
#include "Logger.hpp"

int main(int argc, char *argv[])
{
    Logger::getInstance().log("--- Application Started ---");
    TaskList taskList("tasks.json");

    if (argc < 2)
    {
        TUI::showHelp();
        Logger::getInstance().log("No command provided. Showing help.");
        return 1;
    }

    std::string command = argv[1];

    try
    {
        if (command == "list")
        {
            TUI::displayTasks(taskList.getTasks());
        }
        else if (command == "add")
        {
            if (argc < 4)
            {
                TUI::showMessage("Error: 'add' requires a 'title' and 'description'.");
                TUI::showHelp();
            }
            else
            {
                taskList.addTask(argv[2], argv[3]);
                TUI::showMessage("Task added! 👍");
                TUI::displayTasks(taskList.getTasks());
            }
        }
        else if (command == "done")
        {
            if (argc < 3)
            {
                TUI::showMessage("Error: 'done' requires a task ID.");
            }
            else
            {
                int id = std::stoi(argv[2]);
                if (taskList.markTaskDone(id))
                {
                    TUI::showMessage("Task " + std::to_string(id) + " marked as done. ✅");
                }
                else
                {
                    TUI::showMessage("Error: Task " + std::to_string(id) + " not found. 🤷");
                }
                TUI::displayTasks(taskList.getTasks());
            }
        }
        else if (command == "delete")
        {
            if (argc < 3)
            {
                TUI::showMessage("Error: 'delete' requires a task ID.");
            }
            else
            {
                int id = std::stoi(argv[2]);
                if (taskList.deleteTask(id))
                {
                    TUI::showMessage("Task " + std::to_string(id) + " deleted. 🗑️");
                }
                else
                {
                    TUI::showMessage("Error: Task " + std::to_string(id) + " not found. 🤷");
                }
                TUI::displayTasks(taskList.getTasks());
            }
        }
        else if (command == "clear")
        {
            taskList.deleteDoneTasks();
            TUI::showMessage("All completed tasks cleared. ✨");
            TUI::displayTasks(taskList.getTasks());
        }
        else if (command == "help")
        {
            TUI::showHelp();
        }
        else
        {
            TUI::showMessage("Unknown command: " + command);
            TUI::showHelp();
        }
    }
    catch (const std::invalid_argument &e)
    {
        TUI::showMessage("Error: Invalid ID. Please provide a number.");
        Logger::getInstance().log("Error: Invalid argument for ID.");
    }
    catch (const std::exception &e)
    {
        TUI::showMessage("An unexpected error occurred: " + std::string(e.what()));
        Logger::getInstance().log("CRITICAL ERROR: " + std::string(e.what()));
    }

    Logger::getInstance().log("--- Application Exiting ---");
    return 0;
}
