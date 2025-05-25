#include "framework.h" // Your shared interfaces & utilities
#include "pch.h"

// Basic typdef for tests (Inputs, Outputs)
using DLLSolutionInput  = std::string;
using DLLSolutionOutput = int;

using SolutionTest = TestCase<DLLSolutionInput, DLLSolutionOutput>;

class DLLSolution : public Solution<DLLSolutionInput, DLLSolutionOutput> {
  public:
    // Change the name to represent your task
    std::string name() const override { return "Roman to int"; }

    DLLSolution() {

        // Create tests as vector entries (example below)
        // Tests.push_back(SolutionTest::create({ 3,0,6,1,5 }, 3));

        Tests.push_back(SolutionTest::create("III", 3));
        Tests.push_back(SolutionTest::create("VIII", 8));
    };

    /*  Run the custom function that represents your solution
     *   If no custom function is wanted, it can also be written here
     */
    DLLSolutionOutput run(DLLSolutionInput& Inputs) override { return RomanToInt(Inputs); }

    static int GetValue(char R) {
        if (R == 'I') return 1;
        if (R == 'V') return 5;
        if (R == 'X') return 10;
        if (R == 'L') return 50;
        if (R == 'C') return 100;
        if (R == 'D') return 500;
        if (R == 'M') return 1000;
        return -1;
    }

    static int RomanToInt(std::string& S) {
        int Num = 0;

        for (int i = 0; i < S.length(); i++) {
            int const c1 = GetValue(S[i]);
            if (i + 1 < S.length()) {
                int const c2 = GetValue(S[i + 1]);
                if (c1 >= c2) {
                    Num += c1;
                } else {
                    Num += (c2 - c1);
                    i++;
                }
            } else {
                Num += c1;
            }
        }

        return Num;
    }
};

extern "C" __declspec(dllexport) ISolutionBase* create() {
    return new DLLSolution();
}
