#include "gtest/gtest.h"
#include "util.h"

#include <range/v3/all.hpp>
#include <unformat.h>

using namespace ranges;

TEST(Problems, Day1)
{
	auto input = get_input("../../Input/day1.txt");
	auto data = input
		| view::split('\n')
		| view::transform([](auto i) { return ay::unformat_arg<int>(i); });
	//istream_range<int> data{ std::istringstream(input) };

	// Part 1
	auto result = accumulate(data, 0);

	ASSERT_EQ(590, result);

	// Part 2
	auto cumulative = data
		| view::cycle
		| view::partial_sum();

	std::set<int> seen;
	auto frequency = [&] {
		for (auto f : cumulative)
		{
			if (seen.find(f) != seen.end())
			{
				return f;
			}
			seen.insert(f);
		}
	}();

	ASSERT_EQ(83445, frequency);
}