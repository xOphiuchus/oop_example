#pragma once
#include "BaseTask.hpp"
#include <string>

class Task : public BaseTask
{
public:
    Task(int id, const std::string &title, const std::string &description, bool isDone = false);
    void display() const override;
    nlohmann::json toJson() const override;
    void markDone() override;
    bool isDone() const override;
    int getId() const override;

private:
    int m_id;
    std::string m_title;
    std::string m_description;
    bool m_isDone;
};
