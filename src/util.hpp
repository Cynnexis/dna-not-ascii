#pragma once

#include <iostream>
#include <functional>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cassert>

using std::cout, std::cerr, std::cin, std::endl, std::string;

/**
 * @brief Get the current epoch in milliseconds.
 * @details Source code inspired from https://stackoverflow.com/a/17371925/7347145
 * by Dan Moulding and Raedwald.
 * 
 * @return unsigned long The time in milliseconds starting from January the 1st,
 * 1970.
 */
unsigned long epochMs();
