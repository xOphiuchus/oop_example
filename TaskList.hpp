#pragma once
#include <vector>
#include <string>
#include <memory>
#include "BaseTask.hpp"

class TaskList
{
public:
    TaskList(const std::string &filename);
    ~TaskList();

    void addTask(const std::string &title, const std::string &description);
    bool deleteTask(int id);
    bool markTaskDone(int id);
    void deleteDoneTasks();
    const std::vector<std::unique_ptr<BaseTask>> &getTasks() const;

private:
    std::vector<std::unique_ptr<BaseTask>> m_tasks;
    std::string m_filename;
    int m_nextId;

    void loadTasks();
    void saveTasks() const;
    int getNextId();
};
