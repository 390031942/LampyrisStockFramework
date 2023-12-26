/*
 * File:  Utilities.cpp
 * Brief: 实用工具类
 * Author:wushuhong
 * Date： 20223/12/26
*/

// Project Include(s)
#include "Utilities.h"

std::vector<std::string> Utilities::split(const std::string& str, char delimiter) {
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;

	while (getline(ss, token, delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}
