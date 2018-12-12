#include "gtest/gtest.h"
#include "util.h"

#include <range/v3/all.hpp>

using namespace ranges;

TEST(Problems, Day2)
{
	auto input = get_input("../../Input/day2.txt");
	auto data = input
		| view::split('\n')
		| view::transform([](auto a) { a |= action::sort; return a; });

	// Part 1
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