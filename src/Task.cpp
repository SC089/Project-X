#include "Task.h"
#include <iostream>

Task::Task(const std::string& title, const std::string& description)
    : title(title), description(description), completed(false) {}

std::string Task::getTitle() const {
    return title;
}

std::string Task::getDescription() const {
    return description;
}

bool Task::isCompleted() const {
    return completed;
}

void Task::markComplete() {
    completed = true;
}

void Task::displayTask() const {
    std::cout << (completed ? "[X] " : "[ ] ") << title << ": " << description << std::endl;
}