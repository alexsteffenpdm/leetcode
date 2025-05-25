#include <utility>

#include "framework.h" // Your shared interfaces & utilities
#include "pch.h"

struct GasStationInputs {

    GasStationInputs(std::vector<int> InGas, std::vector<int> InCost)
        : Gas(std::move(std::move(InGas))), Cost(std::move(std::move(InCost))) {}

    std::vector<int> Gas;
    std::vector<int> Cost;
};

using GasStationTest = TestCase<GasStationInputs, int>;

class GasStationSolution : public Solution<GasStationInputs, int> {
  public:
    std::string name() const override { return "Gas Station"; }

    GasStationSolution() {

        Tests.push_back(GasStationTest::create(GasStationInputs({1, 2, 3, 4, 5}, {3, 4, 5, 1, 2}), 3));
        Tests.push_back(GasStationTest::create(GasStationInputs({2, 3, 4}, {3, 4, 3}), -1));
    };

    int run(GasStationInputs& Input) override { return canCompleteCircuit(Input.Gas, Input.Cost); }
    /* Idea: greedy algorithm
     */
    static int canCompleteCircuit(std::vector<int>& gas, std::vector<int>& cost) {
        if (gas.empty()) return -1;

        int start   = 0;
        int total   = 0;
        int current = 0;

        int diff = 0;
        for (int i = 0; i < gas.size(); i++) {
            diff = gas[i] - cost[i];
            total += diff;
            current += diff;
            if (current < 0) {
                start   = i + 1;
                current = 0;
            }
        }

        return total >= 0 ? start : -1;
    }
};

extern "C" __declspec(dllexport) ISolutionBase* create() {
    return new GasStationSolution();
}
