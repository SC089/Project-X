#include "ProjectList.h"
#include <iostream>

ProjectList::ProjectList(const std::string& name) : name(name) {}

std::string ProjectList::getName() const {
    return name;
}

void ProjectList::addTask(const std::string& title, const std::string& description) {
    tasks.emplace_back(title, description);
}

void ProjectList::viewTasks() const {
    if (tasks.empty()) {
        std::cout << "No tasks found.\n";
        return;
    }
    for (size_t i=0; i < tasks.size(); ++i) {
        std::cout << i + 1 << ". ";
        tasks[i].displayTask();
    }
}

void ProjectList::markTaskComplete(int index) {
    if (index < 1 || index > tasks.size()) {
        std::cout << "Invalid task number.\n";
        return;
    }
    tasks[index - 1].markComplete();
}

void ProjectList::deleteTask(int index) {
    if (index < 1 || index > tasks.size()) {
        std::cout << "Invalid task number.\n";
        return;
    }
    tasks.erase(tasks.begin() + (index - 1));
}