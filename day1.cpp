#include "gtest/gtest.h"
#include "util.h"

#include <numeric>

TEST(Problems, Day1)
{
	auto input = get_input("../../Input/day1.txt");
	auto data = string_split<int64>(input, "\n");
	auto result = std::accumulate(data.begin(), data.end(), (int64)0);

	// Part 1
	ASSERT_EQ(590, result);

	std::set<int64> frequencyReached;
	int64 currentFrequency = 0;
	std::size_t index = 0;
	while (frequencyReached.find(currentFrequency) == frequencyReached.end())
	{
		frequencyReached.insert(currentFrequency);
		currentFrequency += data[index++ % data.size()];
	}

	// Part 2
	ASSERT_EQ(83445, currentFrequency);
}