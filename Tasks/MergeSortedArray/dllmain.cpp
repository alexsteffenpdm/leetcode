#include <utility>

#include "framework.h" // Add additional headers here if needed
#include "pch.h"

// Basic typdef for tests (Inputs, Outputs)
// typedef std::vector<int> DLLSolutionInput;

struct DLLSolutionInput {
  public:
    std::vector<int> nums1;
    int              m;

    std::vector<int> nums2;
    int              n;
    DLLSolutionInput(std::vector<int> v1, int m, std::vector<int> v2, int n)
        : nums1(std::move(std::move(v1))), m(m), nums2(std::move(std::move(v2))), n(n) {}
};
using DLLSolutionOutput = std::vector<int>;

using SolutionTest = TestCase<DLLSolutionInput, DLLSolutionOutput>;

class DLLSolution : public Solution<DLLSolutionInput, DLLSolutionOutput> {
  public:
    // Change the name to represent your task
    std::string name() const override { return "Merge Sorted Array"; }

    DLLSolution() {

        // Create tests as vector entries (example below)
        Tests.push_back(SolutionTest::create(DLLSolutionInput({1, 2, 3, 0, 0, 0}, 3, {2, 5, 6}, 3),
                                             DLLSolutionOutput({1, 2, 2, 3, 5, 6})));
    };

    /*  Run the custom function that represents your solution
     *   If no custom function is wanted, it can also be written here
     */
    DLLSolutionOutput run(DLLSolutionInput& Inputs) override {
        DLLSolutionOutput Out;
        MergeSortedArray(Inputs.nums1, Inputs.m, Inputs.nums2, Inputs.n);
        Out = std::move(Inputs.nums1);
        return Out;
    }

    static void MergeSortedArray(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {

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
