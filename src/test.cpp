#include "lrucache.hpp"
#include "gtest/gtest.h"

const int NUM_OF_TEST1_RECORDS = 100;
const int NUM_OF_TEST2_RECORDS = 100;
const int TEST2_CACHE_CAPACITY = 50;
const int TEST_CACHE_CAPACITY = 1;


TEST(CacheTest, SimplePut) {
    cache::lru_cache<int, int> cache_lru(1);
    int value = 0;
    cache_lru.put(7, 777);
    EXPECT_TRUE(cache_lru.exists(7));
    EXPECT_TRUE(cache_lru.get(7,value));
    EXPECT_EQ(777, value);
    int  size = cache_lru.size();
    EXPECT_EQ(TEST_CACHE_CAPACITY, size);
}

TEST(CacheTest, MissingValue) {
    cache::lru_cache<int, int> cache_lru(1);
    int value = 0;
    EXPECT_FALSE(cache_lru.get(7,value));
}

TEST(CacheTest1, KeepsAllValuesWithinCapacity) {
    cache::lru_cache<int, int> cache_lru(TEST2_CACHE_CAPACITY);
    int value = 0;
    for (int i = 0; i < NUM_OF_TEST2_RECORDS; ++i) {
        cache_lru.put(i, i);
    }

    for (int i = 0; i < NUM_OF_TEST2_RECORDS - TEST2_CACHE_CAPACITY; ++i) {
        EXPECT_FALSE(cache_lru.exists(i));
    }

    for (int i = NUM_OF_TEST2_RECORDS - TEST2_CACHE_CAPACITY; i < NUM_OF_TEST2_RECORDS; ++i) {
        EXPECT_TRUE(cache_lru.exists(i));
        EXPECT_TRUE(cache_lru.get(i,value));
    }

    int size = cache_lru.size();
    EXPECT_EQ(TEST2_CACHE_CAPACITY, size);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}
