#pragma once

#include <iostream>
#include <string>

#include <vector>

template <class T, class S>
struct TestCase {

public:
    T Inputs;
    S ExpectedResults;
    TestCase(T Inputs, S ExpectedResults)
        : Inputs(Inputs), ExpectedResults(ExpectedResults) {}

    static TestCase<T, S> create(T Inputs, S ExpectedResults) {
        return TestCase<T, S>(Inputs, ExpectedResults);
    }

    virtual bool validateResults(const S& Results) const {
        if (Results == ExpectedResults) {
            std::cout << "\t" << "Test passed" << std::endl;
            return true;
        }
        else {
            std::cout << "\t" << "Test failed" << std::endl;
            std::cout << "\t" << "Expected: " << ExpectedResults << " Got: " << Results << std::endl;
            return false;
        }
    }
};


class ISolutionBase {
public:

    virtual ~ISolutionBase() = default;
    virtual std::string name() const = 0;
    virtual void RunTests() = 0;
};

template <class T, class S>
class Solution : public ISolutionBase {
public:

    
    std::vector<TestCase<T,S>> Tests;

    virtual ~Solution() = default;
    virtual std::string name() const = 0;

    virtual S run(T& Inputs) = 0;

    virtual void RunTests() {
        for (TestCase<T, S>& Test : Tests)
            Test.validateResults(run(Test.Inputs));
    }
};

template<class T>
inline void VecToString(std::vector<T> vec, std::string& OutStr) {
    if (!vec.empty()) {
        std::ostringstream oss;
        std::copy(vec.begin(), vec.end() - 1, std::ostream_iterator<T>(oss, ","));
        oss << vec.back();
        OutStr = oss.str();
        return;
    }
    OutStr = "";
}

static std::ostream& operator<<(std::ostream& os, const std::vector<int>& output) {
    os << "Vector: [";
    if (output.size() > 0) {
        for (size_t i = 0; i < output.size(); ++i) {
            os << output[i];
            if (i < output.size() - 1)
                os << ", ";
        }
    }
    os << "]\n";
    return os;
}