/*
 * File:  Utilities.h
 * Brief: 实用工具类
 * Author:wushuhong
 * Date： 20223/12/26
*/
#pragma once

// STD Include(s)
#include <vector>  
#include <sstream>  
#include <string>  

namespace Utilities {
	std::vector<std::string> split(const std::string& str, char delimiter);
} // end of namespace "Utilities"