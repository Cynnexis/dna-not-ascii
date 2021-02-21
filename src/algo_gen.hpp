#pragma once
#include "util.hpp"

namespace AlgoGen {
	/**
	 * @brief Find the given @p in the @p sequence.
	 * @details The search occurs between @p start and @p end.
	 * 
	 * @param sequence The whole sequence.
	 * @param sub The sub-sequence to search in @p sequence.
	 * @param start The starting point in the @p sequence. This is useful to
	 * limit the search and thus reducing the search time. Defaults to 0 (the
	 * beginning of the sequence).
	 * @param end The ending point in the @p sequence. This is useful to
	 * limit the search and thus reducing the search time. Defaults to
	 * `std::string::npos` (the end of the sequence).
	 * @return Return the index in the @p sequence where the first occurrence of
	 * @p sub was found between @p start and @p end, or return `-1` if @p sub
	 * couldn't be found. If @p sub is empty, returns 0.
	 * @exception Throws a @ref std::runtime_error if @p sub is empty, or if @p
	 * start and/or @p end is invalid.
	 */
	int find_subsequence(const string& sequence, const string& sub, long start = 0, long end = std::string::npos);
}
