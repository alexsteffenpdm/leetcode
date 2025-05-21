#include "pch.h"
#include "framework.h"  // Add additional headers here if needed

// Basic typdef for tests (Inputs, Outputs)
typedef std::vector<int> DLLSolutionInput;
typedef int DLLSolutionOutput;

typedef TestCase<DLLSolutionInput, DLLSolutionOutput> SolutionTest;

class DLLSolution : public Solution<DLLSolutionInput, DLLSolutionOutput>{
public:

    // Change the name to represent your task
    std::string name() const override { return "Candy"; }

    DLLSolution() {

        // Create tests as vector entries (example below)
        // Tests.push_back(SolutionTest::create({ 3,0,6,1,5 }, 3));

        Tests.push_back(SolutionTest::create({ 1,0,2 }, 5));
        Tests.push_back(SolutionTest::create({ 1,2,2 }, 4));
    };

    /*  Run the custom function that represents your solution 
    *   If no custom function is wanted, it can also be written here
    */
    DLLSolutionOutput run(DLLSolutionInput& Inputs) override {
        return candy(Inputs);
    }

    DLLSolutionOutput candy(DLLSolutionInput& Inputs) {
        DLLSolutionInput children(Inputs.size(),0);
        while (*std::max_element(Inputs.begin(), Inputs.end()) != 0) {
            if (Inputs.size() < 3) {
                std::cout << "Inputsize smaller than 3" << std::endl;
                break;
            }

            for (int i = 1; i < children.size() - 1; i++) {
                int current = Inputs.at(i);
                int left = Inputs.at(i - 1);
                int right = Inputs.at(i + 1);

                if (current > left && current > right)
                    children.at(i)++;

                if (left > current)
                    children.at(i - 1)++;

                if (right > current)
                    children.at(i + 1)++;
                
            }
            std::transform(Inputs.begin(), Inputs.end(), Inputs.begin(), [](int value) { return value - 1; });
            std::string VecStr;
            VecToString<int>(children, VecStr);
            std::cout << VecStr << std::endl;
            
        }

        for (int i = 0; i < children.size(); i++) {
            if (children.at(i) == 0)
                children.at(i)++;
        }   
        std::string VecStr;
        VecToString<int>(children, VecStr);
        std::cout << "Final result: " << VecStr << std::endl;

        return std::accumulate(children.begin(), children.end(), 0);
    }
};

extern "C" __declspec(dllexport) ISolutionBase* create() {
    return new DLLSolution();
}