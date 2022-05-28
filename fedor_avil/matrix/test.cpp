#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "matrix.h"
TableMatrix<int> testTable(3,2);
FlatMatrix<int> testFlat(3,4);
FlatMatrix<int> testFlatCopy = testFlat;
FlatMatrix<int> testFlatCopy2 = FlatMatrix<int>(4,3);
TableMatrix<int> testTableCopy2 = TableMatrix<int>(4,3);
TEST_CASE("Test") {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			testTable[i][j] = 1;
		}
	}
	
	testTable += 1;
	CHECK(testTable.Get(0,1) == 2);
	testTable -= 1;
	CHECK(testTable.Get(1,1) == 1);
	testTable *= 3;
	CHECK(testTable.Get(2, 1) == 3);
	testTable.Resize(3, 3);
	testTable *= testTableCopy2;
	//testik = 1 + testik;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			testFlat[i][j] = 10;
		}
	}
	testFlatCopy = testFlat;
	testFlat += 1;
	CHECK(testFlat.Get(0, 1) == 11);
	testFlat -= 1;
	CHECK(testFlat.Get(1, 1) == 10);
	testFlatCopy *= 3;
	CHECK(testFlatCopy.Get(2, 1) == 30);
	testFlatCopy.Resize(4, 3);
	testFlatCopy *= testFlat;

}