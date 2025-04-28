// src/TaskTest.cpp

#include "Task.h"
#include <iostream>

int main() {
    // Create a task
    Task myTask("Finish Project X", "Complete the C++ CLI app.");

    // Display task (should be incomplete)
    myTask.displayTask();

    // Mark task complete
    myTask.markComplete();

    // Display task again (should be marked complete)
    myTask.displayTask();

    return 0;
}
