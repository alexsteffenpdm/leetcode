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
        DLLSolutionInput children(Inputs.size(), 1);
        // Convert to set for quicker iteration
        std::set<int, std::less<>> SortedValues(Inputs.begin(), Inputs.end());

        // Generate Map: value -> Indicies of value in Inputs
        std::unordered_map<int, DLLSolutionInput> ValueIndexMap;

        // Fill map
        for (int i = 0; i < Inputs.size(); i++) ValueIndexMap[Inputs[i]].push_back(i);

        for (const int Value : SortedValues) {
            for (int const index : ValueIndexMap[Value]) {
                int const Priority = static_cast<int>(std::distance(SortedValues.begin(), SortedValues.find(Value)));
                // middle
                if (index > 0 && index < Inputs.size() - 1) {
                    int const left  = Inputs[index - 1];
                    int const right = Inputs[index + 1];
                    if (Value > left || Value > right) {
                        if (Value != left || Value != right)
                            children[index] = Priority;
                        else
                            children[index] = 1;
                    } else
                        children[index] = Priority;
                } // left end
                else if (index == 0) {
                    int const right = Inputs[index + 1];
                    if (Value > right) children[index] = Priority;
                } // right end
                else if (index == Inputs.size() - 1) {
                    int const left = Inputs[index - 1];
                    if (Value > left) children[index] = Priority;
                }
            }
            std::printf("\tResult vector for value %d : %s\n", Value, VecToString(children).c_str());
        }

        Inputs = children;

        std::printf("\tResult vector: %s\n", VecToString(children).c_str());

        return std::accumulate(children.begin(), children.end(), 0);
    }
};

extern "C" __declspec(dllexport) ISolutionBase* create() {
    return new DLLSolution();
}
