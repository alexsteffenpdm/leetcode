#pragma once

#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

template <class T, class S>
struct TestCase {

  public:
    T Inputs;
    S ExpectedResults;
    TestCase(T Inputs, S ExpectedResults) : Inputs(Inputs), ExpectedResults(ExpectedResults) {}

    static TestCase<T, S> create(T Inputs, S ExpectedResults) { return TestCase<T, S>(Inputs, ExpectedResults); }

    virtual bool validateResults(const S& Results) const {
        if (Results == this->ExpectedResults) {
            std::cout << "\t"
                      << "Test passed" << std::endl;
            return true;
        } else {
            std::cout << "\tTest failed" << std::endl;
            // std::cout << "\tExpected: " << this->ExpectedResults << " Got: " << Results << std::endl;
            return false;
        }
    }
};

class ISolutionBase {
  public:
    virtual ~ISolutionBase()         = default;
    virtual std::string name() const = 0;
    virtual void        RunTests()   = 0;
};

template <class T, class S>
class Solution : public ISolutionBase {
  public:
    std::vector<TestCase<T, S>> Tests;
    Solution()                       = default;
    virtual ~Solution()              = default;
    virtual std::string name() const = 0;

    virtual S run(T& Inputs) = 0;

    virtual void RunTests() {
        for (TestCase<T, S>& Test : Tests) Test.validateResults(run(Test.Inputs));
    }
};

template <class T>
std::string VecToString(const std::vector<T>& vec) {
    std::ostringstream oss;
    oss << "Vector: [";
    for (size_t i = 0; i < vec.size(); ++i) {
        oss << vec[i];
        if (i < vec.size() - 1) {
            oss << ", ";
        }
    }
    oss << "]";
    return oss.str();
}

template <typename T>
std::string SetToString(const std::set<T>& s) {
    std::ostringstream oss;
    oss << "{ ";
    for (const auto& elem : s) {
        oss << elem << " ";
    }
    oss << "}";
    return oss.str();
}
