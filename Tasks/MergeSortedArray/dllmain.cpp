#include "pch.h"
#include "framework.h"  // Add additional headers here if needed

// Basic typdef for tests (Inputs, Outputs)
//typedef std::vector<int> DLLSolutionInput;

struct DLLSolutionInput {
public:
    std::vector<int> nums1;
    int m;

    std::vector<int>nums2;
    int n;
    DLLSolutionInput(std::vector<int>v1, int m, std::vector<int>v2, int n)
        : nums1(v1), m(m), nums2(v2), n(n) {}


};
typedef std::vector<int> DLLSolutionOutput;

typedef TestCase<DLLSolutionInput, DLLSolutionOutput> SolutionTest;

class DLLSolution : public Solution<DLLSolutionInput, DLLSolutionOutput>{
public:

    // Change the name to represent your task
    std::string name() const override { return "Merge Sorted Array"; }

    DLLSolution() {

        // Create tests as vector entries (example below)
        Tests.push_back(SolutionTest::create(DLLSolutionInput({ 1,2,3,0,0,0 },3,{2,5,6},3),{1,2,2,3,5,6}));

    };

    /*  Run the custom function that represents your solution 
    *   If no custom function is wanted, it can also be written here
    */
    DLLSolutionOutput run(DLLSolutionInput& Inputs) override {
        DLLSolutionOutput Out;
        MergeSortedArray(Inputs.nums1,Inputs.m,Inputs.nums2,Inputs.n);
        Out = std::move(Inputs.nums1);
        return Out;
    }

    void MergeSortedArray(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {

        if (n == 0) {
            return;
        }

        if (m == 0) {
            nums1 = nums2;
            return;
        }


        for (int i = m; i < m + n; i++) {
            nums1[i] = nums2[i - m];
        }

        sort(nums1.begin(), nums1.end());
    }
};

extern "C" __declspec(dllexport) ISolutionBase* create() {
    return new DLLSolution();
}