#include "pch.h"
#include "CppUnitTest.h"
#include "../LB10.2A/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            Students students[3];

            students[0].surname = "Smith";
            students[0].course = 2;
            students[0].grade_physics = 80;
            students[0].grade_math = 90;
            students[0].grade_info = 85;

            students[1].surname = "Johnson";
            students[1].course = 3;
            students[1].grade_physics = 85;
            students[1].grade_math = 88;
            students[1].grade_info = 90;

            students[2].surname = "Williams";
            students[2].course = 1;
            students[2].grade_physics = 90;
            students[2].grade_math = 80;
            students[2].grade_info = 70;

            p_sort(students, 3); // Sort students array before performing binary search

            bool found = b_search(students, 3, "Johnson", 3, 85);

            Assert::IsTrue(found);

            found = b_search(students, 3, "Smith", 2, 80);

            Assert::IsTrue(found);

            found = b_search(students, 3, "Williams", 1, 95); // Test with non-existent physics grade

            Assert::IsFalse(found);

		}
	};
}
