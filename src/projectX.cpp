// src/ProjectX.cpp

#include "ProjectList.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

void displayMainMenu() {
    std::cout << "\n===== Project X =====\n";
    std::cout << "1. Create new project list\n";
    std::cout << "2. View all project lists\n";
    std::cout << "3. Manage a project list\n";
    std::cout << "4. Delete a project list\n";
    std::cout << "5. Exit\n";
    std::cout << "Choice: ";
}

void displayProjectMenu(const std::string& name) {
    std::cout << "\n--- Project: " << name << "---\n";
    std::cout << "1. Add task\n";
    std::cout << "2. View tasks\n";
    std::cout << "3. Mark task complete\n";
    std::cout << "4. Delete task\n";
    std::cout << "5. Back to main menu\n";
    std::cout << "Choice: ";
}

void saveToFile(const std::vector<ProjectList>& projects) {
    std::ofstream out("data/savefile.txt");
    if (!out) {
        std::cerr << "Failed to open save file.\n";
        return;
    }

    for (const ProjectList& project : projects) {
        out << "[Project] " << project.getName() << "\n";
        for (const Task& task : project.getTasks()) {
            out << "[Task] "
            << task.getTitle() << " | "
            << task.getDescription() << " | "
            << (task.isCompleted() ? 1 : 0) << "\n";
        }
    }

    out.close();
    std::cout << "Data saved successfully.\n";
}

void loadFromFile(std::vector<ProjectList>& projects) {
    std::ifstream in("data/savefile.txt");
    if (!in) {
        std::cerr << "No save file found. Starting fresh.\n";
        return;
    }

    std::string line;
    ProjectList* currentProject = nullptr;

    while (std::getline(in, line)) {
        if (line.rfind("[Project]", 0) == 0) {
            std::string projectName = line.substr(10);
            projects.emplace_back(projectName);
            currentProject = &projects.back();
        }
        else if (line.rfind("[Task]", 0) == 0 && currentProject) {
            std::string taskData = line.substr(7);
            std::stringstream ss(taskData);
            std::string title, description, completeStr;

            std::getline(ss, title, '|');
            std::getline(ss, description, '|');
            std::getline(ss, completeStr);

            auto trim = [](std::string& s) {
                s.erase(0, s.find_first_not_of(" \t"));
                s.erase(s.find_last_not_of(" \t") + 1);
            };

            trim(title);
            trim(description);
            trim(completeStr);

            currentProject->addTask(title, description);
            if (completeStr == "1") {
                currentProject->markTaskComplete(currentProject->getTasks().size());
            }
        }
    }

    in.close();
    std::cout << "Data loaded successfully.\n";
}

// Made new reusable submenu logic to allow looping back into main menu instead of simply breaking and crashing the program
void runProjectMenu(ProjectList& current, std::vector<ProjectList>& projects) {
    int subChoice;
    while (true) {
        displayProjectMenu(current.getName());
        std::cin >> subChoice;
        std::cin.ignore();

        if (subChoice == 1) {
            std::string title, desc;
            std::cout << "Enter task title: ";
            std::getline(std::cin, title);
            std::cout << "Enter task description: ";
            std::getline(std::cin, desc);
            current.addTask(title, desc);
            saveToFile(projects); // Autosave
        }
        else if (subChoice == 2) {
            current.viewTasks();
            // Nothing is physically changed so an autosave feature is not needed
        }
        else if (subChoice == 3) {
            current.viewTasks();
            int tIndex;
            std::cout << "Enter task number to mark complete: ";
            std::cin >> tIndex;
            std::cin.ignore();
            current.markTaskComplete(tIndex);
            saveToFile(projects); // Autosave
        }
        else if (subChoice == 4) {
            current.viewTasks();
            int tIndex;
            std::cout << "Enter task number to delete: ";
            std::cin >> tIndex;
            std::cin.ignore();
            current.deleteTask(tIndex);
            saveToFile(projects); // Autosave
        }
        else if (subChoice == 5) {
            break; // returns to main menu
        }
        else {
            std::cout << "Invalid choice.\n";
        }
    }
}

int main() {
    std::vector<ProjectList> projects;
    loadFromFile(projects); // Load saved projects
    int mainChoice;

    while (true) {
        displayMainMenu();
        std::cin >> mainChoice;
        std::cin.ignore();

        if (mainChoice == 1) {
            std::string name;
            std::cout << "Enter project name: ";
            std::getline(std::cin, name);
            projects.emplace_back(name);
            std::cout << "Project \"" << name << "\" created!\n";

            runProjectMenu(projects.back(), projects);      // submenu for new project, removed saveToFile inside choice 1 because the subMenu now has built in autosaves
        }
        else if (mainChoice == 2) {
            if (projects.empty()) {
                std::cout << "No projects created yet.\n";
                continue;
            }
            std::cout << "\n=== Current Projects ===\n";
            for (size_t i = 0; i < projects.size(); ++i)
                std::cout << i + 1 << ". " << projects[i].getName() << "\n";
        }
        else if (mainChoice == 3) {
            if (projects.empty()) {
                std::cout << "No projects available.\n";
                continue;
            }
            
            std::cout << "\nAvailable Projects:\n";
            for (size_t i = 0; i < projects.size(); ++i)
                std::cout << i + 1 << ". " << projects[i].getName() << "\n";

            int index;
            std::cout << "Enter project number to manage: ";
            std::cin >> index;
            std::cin.ignore();

            if (index < 1 || index > projects.size()) {
                std::cout << "Invalid index.\n";
                continue;
            }

            runProjectMenu(projects[index - 1], projects);  // submenu for existing project
            saveToFile(projects);                 // save after changes
        }
        else if (mainChoice == 4) {
            if (projects.empty()) {
                std::cout << "No projects available to delete.\n";
                continue;
            }

            std::cout << "\nWhich project would you like to delete?\n";
            for (size_t i = 0; i < projects.size(); ++i)
                std::cout << i + 1 << ". " << projects[i].getName() << "\n";

            int delIndex;
            std::cout << "Enter project number to delete: ";
            std::cin >> delIndex;
            std::cin.ignore();

            if (delIndex < 1 || delIndex > projects.size()) {
                std::cout << "Invalid index.\n";
                continue;
            }

            std::cout << "Deleted project: " << projects[delIndex - 1].getName() << "\n";
            projects.erase(projects.begin() + (delIndex - 1));
            saveToFile(projects);
        }
        else if (mainChoice == 5) {
            saveToFile(projects);
            std::cout << "Goodbye!\n";
            break;
        }
        else {
            std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}