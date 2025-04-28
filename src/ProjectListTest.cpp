// src/ProjectListTest.cpp

#include "ProjectList.h"
#include <iostream>

int main() {
    // Create a new project list
    ProjectList myProject("Jarvis AI");

    // Add tasks
    myProject.addTask("Design Voice Commands", "Sketch out basic commands for the AI assistant.");
    myProject.addTask("Implement Reminder System", "Allow setting and getting reminders.");

    // View tasks
    std::cout << "\nCurrent Tasks:\n";
    myProject.viewTasks();

    // Mark the first task complete
    std::cout << "\nMarking first task as complete...\n";
    myProject.markTaskComplete(1);

    // View tasks again
    std::cout << "\nUpdated Tasks:\n";
    myProject.viewTasks();

    // Delete second task
    std::cout << "\nDeleting second task...\n";
    myProject.deleteTask(2);

    // View tasks again
    std::cout << "\nFinal Tasks:\n";
    myProject.viewTasks();

    return 0;
}
