#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack.h"


TEST_CASE("stack") {
    Stack<int> A;
    A.push(1001);
    CHECK(A.Size() == 1);
    CHECK(A.get() == 1001);
    A.push(2022);
    A.push(3);
    CHECK(A.Size() == 3);
    A.pop();
    CHECK(A.Size() == 2);
    CHECK(A.get() == 2022);
    CHECK(A.empty() == false);
    Stack<int> B(A);
    CHECK(A.Size() == B.Size());
    CHECK(A == B);
    A.push(66);
    B.push(66);
    CHECK(A == B);
    std::initializer_list<int> list = { 10, 44, 36, 356, 36 };
    Stack<int> C(list);
    CHECK(C.get() == 10);
    CHECK(C.Size() == 5);
    C.pop();
    CHECK(C.get() == 44);
    CHECK(C.Size() == 4);
    CHECK(C != A);
    Stack<int> D = C;
    CHECK(D == C);
    Stack<int> E;
    CHECK_THROWS_WITH(E.pop(), "Size 0");
    CHECK_THROWS_WITH(E.get(), "size 0");  



    Stack<double> AA;
    AA.push(1.5);
    CHECK(AA.Size() == 1);
    CHECK(AA.get() == 1.5);
    AA.push(2022.2022);
    AA.push(3.3);
    CHECK(AA.Size() == 3);
    AA.pop();
    CHECK(AA.Size() == 2);
    CHECK(AA.get() == 2022.2022);
    CHECK(AA.empty() == false);
    Stack<double> BB(AA);
    CHECK(AA.Size() == BB.Size());
    CHECK(AA == BB);
    AA.push(66);
    BB.push(66);
    CHECK(AA == BB);
    std::initializer_list<double> list_2 = { 10.10, 44.44, 36.36, 356.356, 36.36 };
    Stack<double> CC(list_2);
    CHECK(CC.get() == 10.10);
    CHECK(CC.Size() == 5);
    CC.pop();
    CHECK(CC.get() == 44.44);
    CHECK(CC.Size() == 4);
    CHECK(CC != AA);
    Stack<double> DD = CC;
    CHECK(DD == CC);
    Stack<double> EE;
    CHECK_THROWS_WITH(EE.pop(), "Size 0");
    CHECK_THROWS_WITH(EE.get(), "size 0");
}