// Leetcode.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "Utils/Util.h"
#include <filesystem>
#include <iostream>
#include <memory>
#include <vector>
#include <windows.h>

int main() {

    std::vector<std::pair<std::string, std::unique_ptr<ISolutionBase>>> tasks;
    const std::string                                                   pluginDir = "./build";
    while (true) {
        try {
            for (const auto& entry : std::filesystem::directory_iterator(pluginDir)) {

                if (entry.path().extension() == ".dll") {
                    HMODULE hModule = LoadLibraryA(entry.path().string().c_str());
                    if (!hModule) {
                        DWORD errCode = GetLastError();
                        std::cerr << "Failed to load " << entry.path() << " (Error code: " << errCode << ")\n";
                        continue;
                    }

                    auto create = (ISolutionBase * (*)()) GetProcAddress(hModule, "create");
                    if (!create) {
                        std::cerr << "Missing create() in: " << entry.path() << '\n';
                        FreeLibrary(hModule);
                        continue;
                    }

                    std::unique_ptr<ISolutionBase> task(create());
                    tasks.emplace_back(task->name(), std::move(task));
                }
            }
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Filesystem error: " << e.what() << '\n';
            std::cerr << "Path1: " << e.path1() << '\n';
            std::cerr << "Path2: " << e.path2() << '\n';
            return 1;
        }
        // std::unique_ptr<ISolutionBase> ExitTask = nullptr;
        tasks.emplace_back("Exit", nullptr);

        std::cout << "Available tasks:\n";
        for (size_t i = 0; i < tasks.size(); ++i) std::cout << "\t" << i + 1 << ". " << tasks[i].first << '\n';

        std::cout << "Select task: ";
        int choice = 0;
        std::cin >> choice;

        if (choice == tasks.size()) {
            break;
        }

        if (choice >= 1 && choice <= static_cast<int>(tasks.size())) {
            tasks[choice - 1].second->RunTests();
            std::cout << "\n" << '\n';
        } else {
            std::cout << "Invalid choice.\n";
        }
        tasks.clear();
    }

    return 0;
}
