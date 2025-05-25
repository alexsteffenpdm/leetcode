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
        int const        n = static_cast<int>(citations.size());
        std::vector<int> count(n + 1, 0);

        // Count how many papers have x citations
        for (int const c : citations) {
            if (c >= n) {
                count[n]++; // Count everything >= n in count[n]
            } else {
                count[c]++;
            }
        }

        // Now go backward to find the highest h such that
        // at least h papers have >= h citations
        int total = 0;
        for (int h = n; h >= 0; h--) {
            total += count[h];
            if (total >= h) return h;
        }

        return 0;
    }
};

extern "C" __declspec(dllexport) ISolutionBase* create() {
    return new DLLSolution();
}
