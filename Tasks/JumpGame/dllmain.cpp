#include "pch.h"
#include "framework.h"  // Your shared interfaces & utilities


typedef TestCase<std::vector<int>, bool> JumpGameTest;

class JumpGameSolution : public ISolutionBase {
public:
    std::string name() const override { return "JumpGame"; }

    /*
    IMPORTANT Do via Backtracking!!!!
    */
    bool canJump(std::vector<int>& nums) {
        std::vector<bool> progression(nums.size() - 1, false);

        for (int i = 0; i < nums.size(); i++) {
            if (i < nums.size() - 1) {

                size_t PossibleSteps;
                if (nums.at(i) > progression.size() - i)
                    PossibleSteps = progression.size() - i;
                else
                    PossibleSteps = nums.at(i);

                for (int j = i; j < i + PossibleSteps; j++)
                    progression.at(j) = true;
            }
        }

        std::string boolStr;
        VecToString(progression, boolStr);
        return count(progression.begin(), progression.end(), false) == 0;
    }

    void RunTests() {
        std::vector<JumpGameTest> Tests = {
           JumpGameTest::create({ 2,3,1,1,4 },true),
           JumpGameTest::create({ 3,2,1,0,4 },false),
           JumpGameTest::create({3,0,8,2,0,0,1},true),
           JumpGameTest::create({2,0,1,1,2,1,0,0,0},false),
        };

        for (JumpGameTest Test : Tests)
            Test.validateResults(this->canJump(Test.Inputs));
      
    }
};

extern "C" __declspec(dllexport) ISolutionBase* create() {
    return new JumpGameSolution();
}