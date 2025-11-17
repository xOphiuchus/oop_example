#include "Task.hpp"
#include <iostream>

Task::Task(int id, const std::string &title, const std::string &description, bool isDone)
    : m_id(id), m_title(title), m_description(description), m_isDone(isDone) {}

void Task::display() const
{
    std::cout << std::setw(4) << std::left << m_id
              << "[" << (m_isDone ? "x" : " ") << "] "
              << m_title << std::endl;

    if (!m_description.empty())
    {
        std::cout << "     " << m_description << std::endl;
    }
}

nlohmann::json Task::toJson() const
{
    return {
        {"id", m_id},
        {"title", m_title},
        {"description", m_description},
        {"isDone", m_isDone}};
}

void Task::markDone() { m_isDone = true; }
bool Task::isDone() const { return m_isDone; }
int Task::getId() const { return m_id; }
