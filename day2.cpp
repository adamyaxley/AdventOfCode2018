#include "gtest/gtest.h"
#include "util.h"

#include <range/v3/all.hpp>

using namespace ranges;

TEST(Problems, Day2)
{
	// Part 1
	{
		auto input = get_input("../../Input/day2.txt");
		auto data = input
			| view::split('\n')
			| view::transform([](auto a) { a |= action::sort; return a; });

		auto exactlyTwo = [](auto id) {
			auto grouped = id | view::group_by(std::equal_to<>());
			return any_of(grouped, [](auto g) { return distance(g) == 2; });
		};

		auto exactlyThree = [](auto id) {
			auto grouped = id | view::group_by(std::equal_to<>());
			return any_of(grouped, [](auto g) { return distance(g) == 3; });
		};

		auto exactlyTwoIds = data | view::filter(exactlyTwo);
		auto exactlyThreeIds = data | view::filter(exactlyThree);

		auto result = distance(exactlyTwoIds) * distance(exactlyThreeIds);

		ASSERT_EQ(5434, result);
	}

	// Part 2
	{
		auto input = get_input("../../Input/day2.txt");
		auto list = input | view::split('\n');

		auto boxPairs = view::cartesian_product(list, list)
			| view::filter([](auto& pair) {
				return inner_product(std::get<0>(pair), std::get<1>(pair), 0, 
					std::plus<>(), [](char a, char b) { return a == b ? 0 : 1; }) == 1; })
			| view::take_exactly(1);

		auto boxPair = boxPairs.front();
		auto x = std::get<0>(boxPair);
		auto y = std::get<1>(boxPair);

		//auto result = view::concat(view::set_intersection(x, y), view::set_intersection(x | view::reverse, y | view::reverse));

		auto result = view::transform(x, y, [](char& s0, char& s1) { return std::make_pair(s0, s1); })
			| view::remove_if([](auto& pair) { return pair.first != pair.second; })
			| view::transform([](auto& pair) { return pair.first; })
			| to_<std::string>();

		ASSERT_EQ(std::string("agimdjvlhedpsyoqfzuknpjwt"), result);
	}
}