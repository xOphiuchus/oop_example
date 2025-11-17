#include "TaskList.hpp"
#include "Task.hpp"
#include "Logger.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>

TaskList::TaskList(const std::string &filename)
    : m_filename(filename), m_nextId(1)
{
    loadTasks();
    Logger::getInstance().log("TaskList initialized. Loaded data from " + m_filename);
}

TaskList::~TaskList()
{
    try
    {
        saveTasks();
        Logger::getInstance().log("TaskList destroyed. Saved data to " + m_filename);
    }
    catch (const std::exception &e)
    {
        Logger::getInstance().log("CRITICAL: Failed to save tasks on exit: " + std::string(e.what()));
        std::cerr << "CRITICAL: Failed to save tasks on exit: " << e.what() << std::endl;
    }
}

void TaskList::loadTasks()
{
    std::ifstream file(m_filename);
    if (!file.is_open())
    {
        Logger::getInstance().log("No existing task file found. Starting fresh.");
        return;
    }

    try
    {
        nlohmann::json j;
        file >> j;

        if (!j.is_array())
        {
            Logger::getInstance().log("Task file is not a JSON array. Starting fresh.");
            return;
        }

        for (const auto &item : j)
        {
            auto task = std::make_unique<Task>(
                item.at("id").get<int>(),
                item.at("title").get<std::string>(),
                item.at("description").get<std::string>(),
                item.at("isDone").get<bool>());
            m_tasks.push_back(std::move(task));
        }
    }
    catch (nlohmann::json::exception &e)
    {
        Logger::getInstance().log("Error parsing JSON: " + std::string(e.what()));
        m_tasks.clear();
    }
    file.close();
    m_nextId = getNextId();
}

void TaskList::saveTasks() const
{
    nlohmann::json j = nlohmann::json::array();
    for (const auto &task : m_tasks)
    {
        j.push_back(task->toJson());
    }

    std::ofstream file(m_filename);
    if (file.is_open())
    {
        file << j.dump(4);
        file.close();
    }
    else
    {
        throw std::runtime_error("Could not open file for saving: " + m_filename);
    }
}

int TaskList::getNextId()
{
    if (m_tasks.empty())
        return 1;
    int maxId = 0;
    for (const auto &task : m_tasks)
    {
        if (task->getId() > maxId)
        {
            maxId = task->getId();
        }
    }
    return maxId + 1;
}

void TaskList::addTask(const std::string &title, const std::string &description)
{
    auto newTask = std::make_unique<Task>(m_nextId, title, description);
    m_tasks.push_back(std::move(newTask));
    Logger::getInstance().log("Added task " + std::to_string(m_nextId) + ": " + title);
    m_nextId++;
}

bool TaskList::deleteTask(int id)
{
    auto it = std::find_if(m_tasks.begin(), m_tasks.end(),
                           [id](const auto &task)
                           { return task->getId() == id; });

    if (it != m_tasks.end())
    {
        m_tasks.erase(it);
        Logger::getInstance().log("Deleted task " + std::to_string(id));
        return true;
    }
    Logger::getInstance().log("Failed to delete task " + std::to_string(id) + ": Not found.");
    return false;
}

bool TaskList::markTaskDone(int id)
{
    auto it = std::find_if(m_tasks.begin(), m_tasks.end(),
                           [id](const auto &task)
                           { return task->getId() == id; });

    if (it != m_tasks.end())
    {
        (*it)->markDone();
        Logger::getInstance().log("Marked task " + std::to_string(id) + " as done.");
        return true;
    }
    Logger::getInstance().log("Failed to mark task " + std::to_string(id) + " done: Not found.");
    return false;
}

void TaskList::deleteDoneTasks()
{
    auto new_end = std::remove_if(m_tasks.begin(), m_tasks.end(),
                                  [](const auto &task)
                                  { return task->isDone(); });
    int count = std::distance(new_end, m_tasks.end());
    m_tasks.erase(new_end, m_tasks.end());
    Logger::getInstance().log("Cleared " + std::to_string(count) + " completed tasks.");
}

const std::vector<std::unique_ptr<BaseTask>> &TaskList::getTasks() const
{
    return m_tasks;
}
