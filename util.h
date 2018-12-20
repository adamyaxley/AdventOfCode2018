#pragma once

#include <string>
#include <iostream>

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

struct printer {
	std::ostream &os_;
	bool &first_;

	template<typename T>
	void operator()(T const &t) const
	{
		if (first_) first_ = false;
		else os_ << ',';
		os_ << t;
	}
};

namespace std {
	template<typename... Ts>
	std::ostream &operator<<(std::ostream &os, std::tuple<Ts...> const &t)
	{
		os << '(';
		auto first = true;
		::ranges::tuple_for_each(t, ::printer{ os, first });
		os << ')';
		return os;
	}
}