#include "framework.h" // Add additional headers here if needed
#include "pch.h"

// Basic typdef for tests (Inputs, Outputs)
using DLLSolutionInput  = std::vector<int>;
using DLLSolutionOutput = int;

using SolutionTest = TestCase<DLLSolutionInput, DLLSolutionOutput>;

class DLLSolution : public Solution<DLLSolutionInput, DLLSolutionOutput> {
  public:
    // Change the name to represent your task
    std::string name() const override { return "Candy"; }

    DLLSolution() {

        // Create tests as vector entries (example below)
        // Tests.push_back(SolutionTest::create({ 3,0,6,1,5 }, 3));

        Tests.push_back(SolutionTest::create({1, 0, 2}, 5));
        Tests.push_back(SolutionTest::create({1, 2, 2}, 4));

        Tests.push_back(SolutionTest::create({1, 2, 87, 87, 87, 2, 1}, 13));
        // Above test should be 13 with {1,2,3,1,3,2,1}
    };

    /*  Run the custom function that represents your solution
     *   If no custom function is wanted, it can also be written here
     */
    DLLSolutionOutput run(DLLSolutionInput& Inputs) override { return candy(Inputs); }

    static DLLSolutionOutput candy(DLLSolutionInput& Inputs) {
        // Each child gets at least once candy
        DLLSolutionInput candies(Inputs.size(), 1);
        // Convert to set for quicker iteration

        for (int i = 1; i < Inputs.size(); i++) {
            if (Inputs[i] > Inputs[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }

        for (int i = static_cast<int>(Inputs.size()) - 2; i >= 0; i--) {
            if (Inputs[i] > Inputs[i + 1]) {
                candies[i] = max(candies[i], candies[i + 1] + 1);
            }
        }

        Inputs = candies;

        return std::accumulate(candies.begin(), candies.end(), 0);
    }
};

extern "C" __declspec(dllexport) ISolutionBase* create() {
    return new DLLSolution();
}
