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

        Tests.push_back(SolutionTest::create({3, 0, 6, 1, 5}, 3));
        Tests.push_back(SolutionTest::create({3, 0, 6, 1, 5}, 3));
        Tests.push_back(SolutionTest::create({1}, 1));
        Tests.push_back(SolutionTest::create({100}, 1));
    };

    /*  Run the custom function that represents your solution
     *   If no custom function is wanted, it can also be written here
     */
    DLLSolutionOutput run(DLLSolutionInput& Inputs) override { return hIndex(Inputs); }

    static int hIndex(std::vector<int>& citations) {

        int const        index  = 0;
        int const        cnt    = 0;
        std::vector<int> sorted = citations;
        std::sort(sorted.begin(), sorted.end(), std::greater<int>());

        for (int i = 1; i <= sorted.size(); i++) {
            if (sorted[i - 1] <= i) return i;
        }

        return 0;
    }
};

extern "C" __declspec(dllexport) ISolutionBase* create() {
    return new DLLSolution();
}
