// Copyright 2023 Tsvetkov
#include <gtest/gtest.h>
#include "./hoara_and_betcher.h"

TEST(HoaraBetcher, Test_1_Hoara_10_elems) {
int array[10];
GetMas(array, 10);
std::vector<int> vector(array, array + 10);
std::sort(vector.begin(), vector.end());
HoaraSort(array, 0, 9);
std::vector<int> vector2(array, array + 10);
ASSERT_EQ(vector2, vector);
}

TEST(HoaraBetcher, Test_2_Betcher_10_plus_10_elems) {
int n = 10;
int* a;
int* b;
int* res;
std::vector<int> av;
std::vector<int> bv;
std::vector<int> res1;
std::vector<int> res2;
res = new int[n * 2];
a = new int[n];
b = new int[n];
GetMas(a, n);
GetMas(b, n);
HoaraSort(a, 0, n - 1);
HoaraSort(b, 0, n - 1);
av.assign(a, a+n);
bv.assign(b, b+n);
BetcherSort(a, b, n, n, res);
res1.assign(res, res + 2 * n);
res2.insert(res2.begin(), av.begin(), av.end());
res2.insert(res2.end(), bv.begin(), bv.end());
std::sort(res2.begin(), res2.end());
ASSERT_EQ(res1, res2);
delete [] a;
delete [] b;
delete [] res;
}

TEST(HoaraBetcher, Test_3_Hoara_20_elems) {
int array[20];
GetMas(array, 20);
std::vector<int> vector(array, array + 20);
std::sort(vector.begin(), vector.end());
HoaraSort(array, 0, 19);
std::vector<int> vector2(array, array + 20);
ASSERT_EQ(vector2, vector);
}

TEST(HoaraBetcher, Test_4_Betcher_20_plus_20_elems) {
int n = 20;
int* a;
int* b;
int* res;
std::vector<int> av;
std::vector<int> bv;
std::vector<int> res1;
std::vector<int> res2;
res = new int[n * 2];
a = new int[n];
b = new int[n];
GetMas(a, n);
GetMas(b, n);
HoaraSort(a, 0, n - 1);
HoaraSort(b, 0, n - 1);
av.assign(a, a+n);
bv.assign(b, b+n);
BetcherSort(a, b, n, n, res);
res1.assign(res, res + 2 * n);
res2.insert(res2.begin(), av.begin(), av.end());
res2.insert(res2.end(), bv.begin(), bv.end());
std::sort(res2.begin(), res2.end());
ASSERT_EQ(res1, res2);
delete [] a;
delete [] b;
delete [] res;
}

TEST(HoaraBetcher, Test_5_Betcher_26_plus_26_elems) {
int n = 26;
int* a;
int* b;
int* res;
std::vector<int> av;
std::vector<int> bv;
std::vector<int> res1;
std::vector<int> res2;
res = new int[n * 2];
a = new int[n];
b = new int[n];
GetMas(a, n);
GetMas(b, n);
HoaraSort(a, 0, n - 1);
HoaraSort(b, 0, n - 1);
av.assign(a, a + n);
bv.assign(b, b + n);
BetcherSort(a, b, n, n, res);
res1.assign(res, res + 2 * n);
res2.insert(res2.begin(), av.begin(), av.end());
res2.insert(res2.end(), bv.begin(), bv.end());
std::sort(res2.begin(), res2.end());
ASSERT_EQ(res1, res2);
delete [] a;
delete [] b;
delete [] res;
}


