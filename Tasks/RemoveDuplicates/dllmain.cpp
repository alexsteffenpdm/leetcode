#include "framework.h" // Add additional headers here if needed
#include "pch.h"

// Basic typdef for tests (Inputs, Outputs)
using DLLSolutionInput  = std::vector<int>;
using DLLSolutionOutput = int;

using SolutionTest = TestCase<DLLSolutionInput, DLLSolutionOutput>;

class DLLSolution : public Solution<DLLSolutionInput, DLLSolutionOutput> {
  public:
    // Change the name to represent your task
    std::string name() const override { return "Remove Duplicates"; }

    DLLSolution() {

        // Create tests as vector entries (example below)
        Tests.push_back(SolutionTest::create({1, 1, 2}, 2));
        Tests.push_back(SolutionTest::create({0, 0, 1, 1, 1, 2, 2, 3, 3, 4}, 5));
    };

    /*  Run the custom function that represents your solution
     *   If no custom function is wanted, it can also be written here
     */
    DLLSolutionOutput run(DLLSolutionInput& Inputs) override { return customFunction(Inputs); }

    static DLLSolutionOutput customFunction(DLLSolutionInput& Inputs) {
        const int     replacer = 101;
        int           counter  = 0;
        std::set<int> knownElements;
        for (auto i = Inputs.begin(); i < Inputs.end(); i++) {
            if (knownElements.contains(*i)) {
                *i = replacer;
            } else {
                knownElements.insert(*i);
                counter++;
            }
        }
        std::sort(Inputs.begin(), Inputs.end());
        return counter;
        return DLLSolutionOutput();
    }
};

extern "C" __declspec(dllexport) ISolutionBase* create() {
    return new DLLSolution();
}
