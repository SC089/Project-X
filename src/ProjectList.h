#ifndef PROJECTLIST_H
#define PROJECTLIST_H

#include "Task.h"
#include <vector>
#include <string>

class ProjectList {
private:
    std::string name;
    std::vector<Task> tasks;

public:
    // Constructor
    ProjectList(const std::string& name);

    // Getters
    std::string getName() const;

    // Core functions
    void addTask(const std::string& title, const std::string& description);
    void viewTasks() const;
    void markTaskComplete(int index);
    void deleteTask(int index);
};

#endif 
