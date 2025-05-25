#include "framework.h" // Add additional headers here if needed
#include "pch.h"

// Basic typdef for tests (Inputs, Outputs)
using DLLSolutionInput  = std::vector<int>;
using DLLSolutionOutput = int;

using SolutionTest = TestCase<DLLSolutionInput, DLLSolutionOutput>;

class DLLSolution : public Solution<DLLSolutionInput, DLLSolutionOutput> {
  public:
    // Change the name to represent your task
    std::string name() const override { return "HIndex"; }

    DLLSolution() {
        // Create tests as vector entries (example below)
        // Tests.push_back(SolutionTest::create({ 3,0,6,1,5 }, 3));
    };

    /*  Run the custom function that represents your solution
     *   If no custom function is wanted, it can also be written here
     */

    DLLSolutionOutput run(DLLSolutionInput& Inputs) override { return customFunction(Inputs); }

    static DLLSolutionOutput customFunction(DLLSolutionInput& /*Inputs*/) { return DLLSolutionOutput(); }
};

extern "C" __declspec(dllexport) ISolutionBase* create() {
    return new DLLSolution();
}
