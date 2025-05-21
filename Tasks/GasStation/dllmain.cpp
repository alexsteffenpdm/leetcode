#include "pch.h"
#include "framework.h"  // Your shared interfaces & utilities

struct GasStationInputs {

    GasStationInputs(std::vector<int> InGas, std::vector<int> InCost)
        : Gas(InGas), Cost(InCost) {
    }

    std::vector<int> Gas;
    std::vector<int> Cost;
};

typedef TestCase<GasStationInputs, int> GasStationTest;

class GasStationSolution : public Solution<GasStationInputs, int> {
public:
    std::string name() const override { return "Gas Station"; }

    GasStationSolution() {

        Tests.push_back(GasStationTest::create(GasStationInputs({ 1,2,3,4,5 }, { 3,4,5,1,2 }), 3));
        Tests.push_back(GasStationTest::create(GasStationInputs({ 2,3,4 }, { 3,4,3 }), -1));
    };

    int run(GasStationInputs& Input) override {

        return canCompleteCircuit(Input.Gas, Input.Cost);
    }

    int canCompleteCircuit(std::vector<int>& gas, std::vector<int>& cost) {
        std::vector<int> residue(gas.size(), 0);
        std::transform(gas.begin(), gas.end(), cost.begin(), residue.begin(), std::minus<int>());
        int start = -1;
        int tank = 0;
        for (int i = 0; i < residue.size(); i++)
            if (residue[i] > 0) {
                tank = residue[i] > tank ? residue[i] : tank;
                start = i;
            }

        if (start >= 0) {
            return start;
        }

        return -1;
    }

};

extern "C" __declspec(dllexport) ISolutionBase* create() {
    return new GasStationSolution();
}