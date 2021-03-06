#include "gtest/gtest.h"
#include "util.h"

#include <range/v3/all.hpp>
#include <unformat.h>

using namespace ranges;

struct Claim
{
	int id;
	int x, y;
	int w, h;
};

namespace std {
	std::ostream &operator<<(std::ostream &os, Claim const &t)
	{
		os << "{" << t.id << "," << t.x << "," << t.y << "," << t.w << "," << t.h << "}";
		return os;
	}
}

TEST(Problems, Day3)
{
	auto input = get_input("../../Input/day3.txt");
	//auto input = std::string("#1 @ 1,3: 4x4\n#2 @ 3,1: 4x4\n#3 @ 5,5: 2x2");

	auto claims = input
		| view::split('\n')
		| view::transform([&](auto s) {
		Claim claim;
		constexpr auto format = ay::make_format("#{} @ {},{}: {}x{}");
		ay::unformat(s, format, claim.id, claim.x, claim.y, claim.w, claim.h);
		return claim; })
		| to_vector;

	// Part 1
	{
		auto pixels = view::for_each(claims, [](auto& claim) {
			return yield_from(view::cartesian_product(
				view::iota(claim.x, claim.x + claim.w),
				view::iota(claim.y, claim.y + claim.h))); })
			| to_vector;

		pixels = pixels | move | action::unique | action::sort;

		auto overlappingPixels = pixels
			| view::group_by(std::equal_to<>())
			| view::remove_if([](auto& pixelGroup) {
				return distance(pixelGroup) == 1; });

		auto result = distance(overlappingPixels);

		ASSERT_EQ(119551, result);
	}

	// Part 2
	{
		auto disjointClaims = claims
			| view::transform([&](auto& claim) {
				return std::make_pair(claim, view::all(claims)); })
			| view::filter([](auto& pair) {
				auto& a = pair.first;
				auto& bs = pair.second;
				return all_of(bs, [&](auto& b) {
					if (a.id == b.id)
					{
						return true;
					}
					// A doesn't overlap with B
					return (a.x > b.x + b.w || a.x + a.w < b.x || a.y > b.y + b.h || a.y + a.h < b.y); }); });

		ASSERT_EQ(1, distance(disjointClaims));
		ASSERT_EQ(1124, disjointClaims.front().first.id);
	}
}