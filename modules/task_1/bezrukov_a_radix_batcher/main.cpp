// Copyright 2023 Bezrukov Aleksandr
#include "./radix_batcher.h"

// ----------------<radix sort>------------------------
// test for [100, 99, 98, ..., 2, 1] -> [1, 2, ..., 99, 100]
TEST(RadixSortBatcherSeq, isCorrectOnStrictAscending) {
    const int size = 100;
    const int startValue = 100;
    std::vector<uint32_t> data(size);
    fillStrictDescending<uint32_t>(data.data(), size, startValue);
    radixSort<uint32_t>(&data, 0, size);
    ASSERT_TRUE(isStrictAscending<uint32_t>(data.data(), size, 1));
}

// test for [100, 99, 98, ..., 2, 1] -> [51, 52, ..., 99, 100] + [1, 2, ..., 49, 50]
TEST(RadixSortBatcherSeq, canSortBlock_size_even_blockSize_half) {
    const int size = 100;
    const int halfSize = size / 2;
    const int startValue = 100;
    std::vector<uint32_t> data(size);
    fillStrictDescending<uint32_t>(data.data(), size, startValue);
    radixSort<uint32_t>(&data, 0, halfSize);
    radixSort<uint32_t>(&data, halfSize, halfSize);
    ASSERT_TRUE(isStrictAscending<uint32_t>(data.data(), halfSize, 51));
    ASSERT_TRUE(isStrictAscending<uint32_t>(data.data() + halfSize, halfSize, 1));
}

// test for [100, 99, 98, ..., 2, 1] -> [100] + [1, 2, ..., 98, 99]
TEST(RadixSortBatcherSeq, canSortBlock_size_even_blockSize_n_minus_one_1) {
    const int size = 100;
    const int startValue = 100;
    std::vector<uint32_t> data(size);
    fillStrictDescending<uint32_t>(data.data(), size, startValue);
    radixSort<uint32_t>(&data, 1, size - 1);
    ASSERT_TRUE(isStrictAscending<uint32_t>(data.data() + 1, size - 1, 1));
}

// test for [100, 99, 98, ..., 2, 1] -> [2, 3, ..., 99, 100] + [1]
TEST(RadixSortBatcherSeq, canSortBlock_size_even_blockSize_n_minus_one_2) {
    const int size = 100;
    const int startValue = 100;
    std::vector<uint32_t> data(size);
    fillStrictDescending<uint32_t>(data.data(), size, startValue);
    radixSort<uint32_t>(&data, 0, size - 1);
    ASSERT_TRUE(isStrictAscending<uint32_t>(data.data(), size - 1, 2));
}

// test for [99] -> [99]
TEST(RadixSortBatcherSeq, canSortLengthOne) {
    const int size = 1;
    std::vector<uint32_t> data(size);
    data[0] = 99;
    ASSERT_NO_THROW(radixSort<uint32_t>(&data, 0, 1));
    ASSERT_EQ(data[0], 99U);
}

// can sort rand values
TEST(RadixSortBatcherSeq, canSortRandValuesRandSize) {
    const uint32_t size = getRandValue<uint32_t>(101, 404);
    std::vector<uint32_t> data(size);
    fillVecWithRandValues<uint32_t>(data.data(), size, 0, 4512);
    radixSort<uint32_t>(&data, 0, size);
    ASSERT_TRUE(isAscending<uint32_t>(data.data(), size));
}

// can sort ushort
TEST(RadixSortBatcherSeq, canSortUSHORT) {
    const int size = 100;
    std::vector<uint16_t> data(size);
    fillVecWithRandValues<uint16_t>(data.data(), size, 0, 65535);
    radixSort<uint16_t>(&data, 0, size);
    ASSERT_TRUE(isAscending<uint16_t>(data.data(), size));
}
// ----------------</radix sort>------------------------


// ----------------<merge check>------------------------

// test for [51, 52, ..., 99, 100, 1, 2, ..., 49, 50] -> [1, 2, ..., 99, 100]
// vector with 2 blocks of same size (50)
TEST(mergeCheck, sameBlockSize) {
    const int size = 100;
    const int blockSize = size / 2;
    std::vector<uint32_t> data(size);
    fillStrictAscending<uint32_t>(data.data(), blockSize, 51);
    fillStrictAscending<uint32_t>(data.data() + blockSize, blockSize, 1);
    std::vector<uint32_t> resFragment1(blockSize);
    std::vector<uint32_t> resFragment2(blockSize);
    mergeFragments<uint32_t>(&data, &resFragment1, 0, blockSize, blockSize, blockSize, true);
    mergeFragments<uint32_t>(&data, &resFragment2, 0, blockSize, blockSize, blockSize, false);
    ASSERT_TRUE(isStrictAscending<uint32_t>(resFragment1.data(), blockSize, 1));
    ASSERT_TRUE(isStrictAscending<uint32_t>(resFragment2.data(), blockSize, 51));
}
// ----------------</merge check>------------------------

// ----------------<algorithm check>------------------------

/*
* test 1
* scheme:
* ---------------------
*            |
* ---------------------
*/
TEST(radix_batchers_mergesort, test1_blocksCount_2) {
    const int size = 100;
    const int blockSize1 = size / 2;
    const int blockSize2 = size / 2;

    std::vector<uint32_t> data(size);
    fillVecWithRandValues<uint32_t>(data.data(), size, 0, 142124);
    std::vector<uint32_t> checkVector(data);

    std::vector<uint32_t> fragment1(blockSize1);
    std::vector<uint32_t> fragment2(blockSize2);

    radixSort<uint32_t>(&data, 0, blockSize1);
    radixSort<uint32_t>(&data, blockSize1, blockSize2);

    mergeFragments<uint32_t>(&data, &fragment1, 0, blockSize1, blockSize1, blockSize2, true);
    mergeFragments<uint32_t>(&data, &fragment2, 0, blockSize1, blockSize1, blockSize2, false);

    for (int i = 0; i < blockSize1; i++)
        data[i] = fragment1[i];
    for (int i = 0; i < blockSize2; i++)
        data[i + blockSize1] = fragment2[i];

    // check if correct
    radixSort<uint32_t>(&checkVector, 0, size);

    ASSERT_TRUE(isVecSame<uint32_t>(data, checkVector));
}

/*
* test 2
* scheme:
* -------------------
*        |
* -------------------
*   |          |
* -------------------
*/
TEST(radix_batchers_mergesort, test1_blocksCount_3) {
    const int size = 99;
    const int blockCount = 3;
    const int blockSize1 = size / blockCount;
    const int blockSize2 = size / blockCount;
    const int blockSize3 = size / blockCount;

    std::vector<uint32_t> data(size);
    fillVecWithRandValues<uint32_t>(data.data(), size, 0, 142124);
    std::vector<uint32_t> checkVector(data);

    std::vector<uint32_t> fragment1(blockSize1);
    std::vector<uint32_t> fragment2(blockSize2);
    std::vector<uint32_t> fragment3(blockSize3);

    radixSort<uint32_t>(&data, 0, blockSize1);
    radixSort<uint32_t>(&data, blockSize1, blockSize2);
    radixSort<uint32_t>(&data, blockSize1 + blockSize2, blockSize3);


    // Batcher's merge network routine

    // stage 1 step 1: merging (2, 3)
    mergeFragments<uint32_t>(&data, &fragment2, blockSize1, blockSize2, blockSize1 + blockSize2, blockSize3, true);
    mergeFragments<uint32_t>(&data, &fragment3, blockSize1, blockSize2, blockSize1 + blockSize2, blockSize3, false);

    for (int i = 0; i < blockSize2; i++)
        data[i + blockSize1] = fragment2[i];
    for (int i = 0; i < blockSize3; i++)
        data[i + blockSize1 + blockSize2] = fragment3[i];

    // stage 2 step 1: merging (1, 2)
    mergeFragments<uint32_t>(&data, &fragment1, 0, blockSize1, blockSize1, blockSize2, true);
    mergeFragments<uint32_t>(&data, &fragment2, 0, blockSize1, blockSize1, blockSize2, false);

    for (int i = 0; i < blockSize1; i++)
        data[i] = fragment1[i];
    for (int i = 0; i < blockSize2; i++)
        data[i + blockSize1] = fragment2[i];

    // stage 2 step 2: merging (2,3)
    mergeFragments<uint32_t>(&data, &fragment2, blockSize1, blockSize2, blockSize1 + blockSize2, blockSize3, true);
    mergeFragments<uint32_t>(&data, &fragment3, blockSize1, blockSize2, blockSize1 + blockSize2, blockSize3, false);

    for (int i = 0; i < blockSize2; i++)
        data[i + blockSize1] = fragment2[i];
    for (int i = 0; i < blockSize3; i++)
        data[i + blockSize1 + blockSize2] = fragment3[i];

    // check if correct
    radixSort<uint32_t>(&checkVector, 0, size);

    ASSERT_TRUE(isVecSame<uint32_t>(data, checkVector));
}
// ----------------</algorithm check>------------------------

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
