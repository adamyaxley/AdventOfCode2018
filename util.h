#pragma once

#include <string>
#include <iostream>

#include "External/Unformat/unformat.h"

using namespace ay;

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