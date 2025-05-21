#include "pch.h"
#include "framework.h"  // Your shared interfaces & utilities


enum class RomanNumbers : int
{
	I = 1,
	V = 5,
	X = 10,
	L = 50,
	C = 100,
	D = 500,
	M = 1000,
};


// Basic typdef for tests (Inputs, Outputs)
typedef std::string DLLSolutionInput;
typedef int DLLSolutionOutput;

typedef TestCase<DLLSolutionInput, DLLSolutionOutput> SolutionTest;

class DLLSolution : public Solution<DLLSolutionInput, DLLSolutionOutput> {
public:

	// Change the name to represent your task
	std::string name() const override { return "Roman to int"; }

	DLLSolution() {

		// Create tests as vector entries (example below)
		// Tests.push_back(SolutionTest::create({ 3,0,6,1,5 }, 3));

		Tests.push_back(SolutionTest::create("III", 3));
		Tests.push_back(SolutionTest::create("VIII", 8));
	};

	/*  Run the custom function that represents your solution
	*   If no custom function is wanted, it can also be written here
	*/
	DLLSolutionOutput run(DLLSolutionInput& Inputs) override {
		return RomanToInt(Inputs);
	}

	int checkSecondary(char First, char Second) {
		if (First == 'I') {				// I
			if (Second == 'V')
				return 4;
			else if (Second == 'X')
				return 9;
			else
				return static_cast<int>(RomanNumbers::I);
		}
		else if (First == 'X') {		// X
			if (Second == 'L')
				return 40;
			else if (Second == 'C')
				return 90;
			else
				return static_cast<int>(RomanNumbers::X);
		}
		else if (First == 'C') {		// C
			if (Second == 'D')
				return 400;
			else if (Second == 'M')
				return 900;
			else
				return static_cast<int>(RomanNumbers::C);
		}
		return -1;
	}

	int RomanToInt(std::string& S) {
		int Num = 0;
		bool bUsedSecondary = false;
		for (int i = 0; i < S.size(); i++) {
			char C = S.at(i);
			char C2 = i + 1 < S.size() ? S.at(i + 1) : 'n';
			switch (C) {
			case 'M': Num += static_cast<int>(RomanNumbers::M); break;
			case 'D': Num += static_cast<int>(RomanNumbers::D); break;
			case 'C': Num += checkSecondary(C, C2); bUsedSecondary = true; break;
			case 'L': Num += static_cast<int>(RomanNumbers::L); break;
			case 'X': Num += checkSecondary(C, C2); bUsedSecondary = true; break;
			case 'V': Num += static_cast<int>(RomanNumbers::V); break;
			case 'I': Num += checkSecondary(C, C2); bUsedSecondary = true; break;
			default: break;
			}

			if (C2 != 'n' && bUsedSecondary)
				i++;

			bUsedSecondary = false;
		}
		return Num;
	}
	
};

extern "C" __declspec(dllexport) ISolutionBase* create() {
	return new DLLSolution();
}