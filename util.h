#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <map>
#include <cassert>
#include <initializer_list>
#include <iomanip>
#include <functional>
#include <queue>
#include <set>
#include <bitset>
#include "External/Unformat/unformat.h"
using namespace ay;

using int64 = long long;

#undef min
#undef max

template <typename T>
T sum(const std::vector<T>& vector)
{
	T result = 0;
	for (auto& e : vector)
	{
		result += e;
	}
	return result;
}

template <typename T>
void sort(std::vector<T>& vector)
{
	std::sort(vector.begin(), vector.end());
}

template <typename T>
void sort_desc(std::vector<T>& vector)
{
	std::sort(vector.begin(), vector.end(), std::greater<T>());
}

template <typename T>
std::vector<T> to_vector(const std::string& input)
{
	std::stringstream stream(input);
	std::vector<T> result;
	T element;
	while (stream >> element)
	{
		result.push_back(element);
	}
	return result;
}

template <typename T>
std::vector<std::vector<T>> to_matrix(const std::string& input)
{
	std::string line;
	std::stringstream stream(input);
	std::vector<std::vector<T>> result;
	while (std::getline(stream, line))
	{
		result.push_back(to_vector<T>(line));
	}
	return result;
}

template <typename T>
std::string gen_hash(const std::vector<T>& input)
{
	std::ostringstream result;
	for (auto& e : input)
	{
		result << std::to_string(e);
	}
	return result.str();
}

template <typename T>
std::size_t max_index(const std::vector<T>& input)
{
	assert(input.size() > 0);

	T max = input[0];
	std::size_t index = 0;
	for (std::size_t i = 1; i < input.size(); i++)
	{
		if (input[i] > max)
		{
			max = input[i];
			index = i;
		}
	}
	return index;
}

template <typename T>
T max(const std::vector<T>& input)
{
	return input[max_index(input)];
}

template <typename T>
std::size_t min_index(const std::vector<T>& input)
{
	assert(input.size() > 0);

	T min = input[0];
	std::size_t index = 0;
	for (std::size_t i = 1; i < input.size(); i++)
	{
		if (input[i] < min)
		{
			min = input[i];
			index = i;
		}
	}
	return index;
}

template <typename T>
T min(const std::vector<T>& input)
{
	return input[minIndex(input)];
}

template <typename T>
std::string string_join(const T container, const std::string& delim)
{
	std::ostringstream result;
	for (auto it = std::cbegin(container); it != std::cend(container); it++)
	{
		result << *it;
		auto it2 = it;
		it2++;
		if (it2 != std::cend(container))
		{
			result << delim;
		}
	}
	return result.str();
}

template <typename T = std::string>
std::vector<T> string_split(const std::string& input, const std::string& delim)
{
	std::istringstream stream(input);
	std::vector<T> result;
	std::size_t from = 0;
	while (true)
	{
		const std::size_t to = input.find(delim, from);
		const std::string view = [&]() {
			if (to == std::string::npos)
			{
				return std::string(&input[from]);
			}
			else
			{
				return std::string(&input[from], to - from);
			}
		}();
		if constexpr(std::is_same_v<std::string, T>)
		{
			result.push_back(view);
		}
		else
		{
			std::istringstream stream(view);
			T element;
			stream >> element;
			result.push_back(element);
		}
		if (to == std::string::npos)
		{
			break;
		}
		from = to + delim.length();
	}
	return result;
}

template <typename T>
inline std::string stream_remainder(T& stream)
{
	std::stringstream tmp;
	tmp << stream.rdbuf();
	return tmp.str();
}

inline void string_replace(std::string& input, const std::string& what, const std::string& with)
{
	while (true)
	{
		auto found = input.find(what);
		if (found == std::string::npos)
		{
			break;
		}
		input.replace(found, what.length(), with);
	}
}

inline void string_erase(std::string& input, std::initializer_list<std::string> what)
{
	for (auto it = std::begin(what); it != std::end(what); it++)
	{
		string_replace(input, *it, "");
	}
}

inline std::string get_input(const char* path)
{
	std::string result;
	FILE* handle;
	fopen_s(&handle, path, "r");

	if (!handle)
	{
		throw std::exception();
	}

	while (!feof(handle))
	{
		char buffer[1024];
		buffer[0] = '\0';
		fgets(buffer, sizeof(buffer), handle);
		std::string next(buffer);
		result += next;
	}

	fclose(handle);

	// Remove the last end of line
	if (result.back() == '\n')
	{
		result.pop_back();
	}

	return result;
}

#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)

inline std::string knot_hash(const std::string& input)
{
	std::vector<int> bytes;
	bytes.reserve(input.size() + 5);
	for (auto c : input)
	{
		bytes.push_back((int)c);
	}

	bytes.push_back(17);
	bytes.push_back(31);
	bytes.push_back(73);
	bytes.push_back(47);
	bytes.push_back(23);

	std::vector<int> output;
	output.resize(256);
	for (int i = 0; i < 256; i++)
	{
		output[i] = i;
	}

	int skip = 0;
	int pos = 0;
	for (int i = 0; i < 64; i++)
	{
		for (auto length : bytes)
		{
			for (int j = 0; j < length / 2; j++)
			{
				std::swap(output[(pos + j) % output.size()], output[(pos + length - j - 1) % output.size()]);
			}
			pos += length + skip++;
		}
	}

	std::stringstream hash;

	for (int i = 0; i < 16; i++)
	{
		int block = 0;
		for (int j = 0; j < 16; j++)
		{
			block ^= output[i * 16 + j];
		}

		hash << std::hex << std::setfill('0') << std::setw(2) << block;
	}

	return hash.str();
}

inline std::string to_binary(const std::string& hex)
{
	std::stringstream stream;

	for (auto c : hex)
	{
		int decimal;
		if (c >= 'a')
		{
			decimal = 10 + c - 'a';
		}
		else
		{
			decimal = c - '0';
		}

		for (int i = 3; i >= 0; i--)
		{
			stream << ((decimal & (1 << i)) ? '1' : '0');
		}
	}
	return stream.str();
}