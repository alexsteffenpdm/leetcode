#include "pch.h"
#include "framework.h"  // Add additional headers here if needed

namespace RemoveElement {

// Basic typdef for tests (Inputs, Outputs)
struct DLLSolutionInput {
public:
    std::vector<int> nums;
    int val;

    DLLSolutionInput(std::vector<int> Numbers, int Value) : 
    nums(std::move(Numbers)), val(Value){}
};

// Overload the << operator
static std::ostream& operator<<(std::ostream& os, const DLLSolutionInput& output) {
    os << "DLLSolutionInput {\n";
    os << "  val: " << output.val << ",\n";
    os << "  nums: [";
    if (output.nums.size() > 0) {
        for (size_t i = 0; i < output.nums.size(); ++i) {
            os << output.nums[i];
            if (i < output.nums.size() - 1)
                os << ", ";
        }
    }
    os << "]\n";
    os << "}";
    return os;
}

struct DLLSolutionOutput {
public:
    std::vector<int> nums;
    int size;

    DLLSolutionOutput(std::vector<int> Numbers, int Size) :
        nums(std::move(Numbers)), size(Size) {}
};


// Overload the << operator
static std::ostream& operator<<(std::ostream& os, const DLLSolutionOutput& output) {
    os << "DLLSolutionOutput {\n";
    os << "  size: " << output.size << ",\n";
    os << "  nums: [";
    if (output.nums.size() > 0) {
        for (size_t i = 0; i < output.nums.size(); ++i) {
            os << output.nums[i];
            if (i < output.nums.size() - 1)
                os << ", ";
        }
    }
   
    os << "]\n";
    os << "}";
    return os;
}



//typedef TestCase<DLLSolutionInput, DLLSolutionOutput> SolutionTest;


bool operator==(const DLLSolutionOutput& lhs, const DLLSolutionOutput& rhs) {
    return lhs.size == rhs.size && lhs.nums == rhs.nums;
}



template<class DLLSolutionInput, class DLLSolutionOutput>
class SolutionTest : public TestCase<DLLSolutionInput, DLLSolutionOutput> {
public:

    SolutionTest(DLLSolutionInput Inputs, DLLSolutionOutput Outputs) 
        : TestCase<DLLSolutionInput, DLLSolutionOutput>(Inputs, Outputs) {}

    static SolutionTest create(DLLSolutionInput Inputs, DLLSolutionOutput Outputs) {
        return SolutionTest(Inputs, Outputs);
    }

    bool validateResults(const DLLSolutionOutput& Results) const override {
        // custom validation logic, example:
        int max = 0; int countNonOne = 0;
        if (!Results.nums.empty()) {     
            max = *std::max_element(this->ExpectedResults.nums.begin(), this->ExpectedResults.nums.end());
            countNonOne = static_cast<int>(std::count_if(Results.nums.begin(), Results.nums.end(), [max](int x) { return x != max; }));
        }
        
        if (countNonOne != this->ExpectedResults.size) {
            std::cout << "\t" << "Test failed: size mismatch Got:\n" << countNonOne <<"\nExpected:\n" << this->ExpectedResults << std::endl;
            return false;
        }
        // Compare the expected output nums against the first Results.size elements:
        if (std::equal(Results.nums.begin(), Results.nums.begin() + this->ExpectedResults.size, this->ExpectedResults.nums.begin())) {
            std::cout << "\t" << "Test passed" << std::endl;
            return true;
        }
        else {
            std::cout << "\t" << "Test failed: content mismatch Got:\n" << Results << "\nExpected:\n" << this->ExpectedResults << std::endl;
            return false;
        }
    }
};



class DLLSolution : public Solution<DLLSolutionInput, DLLSolutionOutput>{
public:
    std::vector<SolutionTest<DLLSolutionInput, DLLSolutionOutput>> Tests;
    // Change the name to represent your task
    std::string name() const override { return "Remove Element"; }

    DLLSolution() {

        // Create tests as vector entries (example below)
      
        Tests.push_back(SolutionTest<DLLSolutionInput, DLLSolutionOutput>::create(
            DLLSolutionInput({ 3,2,2,3 }, 3),
            DLLSolutionOutput({ 2,2,4,4 }, 2)
        ));

        Tests.push_back(SolutionTest<DLLSolutionInput, DLLSolutionOutput>::create(
            DLLSolutionInput({ 0,1,2,2,3,0,4,2 }, 2),
            DLLSolutionOutput({ 0,0,1,3,4, 5 ,5, 5 }, 5)
        ));

        Tests.push_back(SolutionTest<DLLSolutionInput, DLLSolutionOutput>::create(
            DLLSolutionInput({}, 0),
            DLLSolutionOutput({}, 0)
        ));

    };

    /*  Run the custom function that represents your solution 
    *   If no custom function is wanted, it can also be written here
    */
    DLLSolutionOutput run(DLLSolutionInput& Inputs) override {
        return removeElement(Inputs.nums,Inputs.val);
    }

    DLLSolutionOutput removeElement(std::vector<int>& Nums, int Value) {
        if (Nums.size() == 0) 
            return DLLSolutionOutput({}, 0);
        
        int max = *std::max_element(Nums.begin(), Nums.end()) +1;
        int NonValueCount = static_cast<int>(std::count_if(Nums.begin(), Nums.end(), [Value](int i) {return i != Value; }));
        std::transform(Nums.begin(), Nums.end(), Nums.begin(),[Value, max](int x){return x == Value ? max : x; });
        //std::transform(Nums.begin(), Nums.end(), Nums.begin(), [Value, max](int x) {return x == max ?  : x; });
        std::sort(Nums.begin(), Nums.end());
        return DLLSolutionOutput(std::move(Nums), NonValueCount);
    }

    void RunTests() override {
        for (SolutionTest<DLLSolutionInput, DLLSolutionOutput>& Test : Tests)
            Test.validateResults(run(Test.Inputs));
    }

};


extern "C" __declspec(dllexport) ISolutionBase* create() {
    return new DLLSolution();
}

}