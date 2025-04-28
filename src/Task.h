#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
private:
    std::string title;
    std::string description;
    bool completed;

public:
    // Constructor
    Task(const std::string& title, const std::string& description);

    // Getters
    std::string getTitle() const;
    std::string getDescription() const;
    bool isCompleted() const;

    // Setters
    void markComplete();

    // Display
    void displayTask() const;
};

#endif
