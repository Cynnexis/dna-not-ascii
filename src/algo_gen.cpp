#include "algo_gen.hpp"

int AlgoGen::find_subsequence(const string& sequence, const string& sub, long start, long end) {
	// If `sub` is empty, returns 0
	if (sub.empty())
		return 0;

	if (end < 0 || end >= sequence.length())
		end = sequence.length() - 1;
	
	if (start < 0)
		start = 0;

	if (start > end)
		throw std::runtime_error("The given search area is not valid: start=" + std::to_string(start) + ", end=" + std::to_string(end));

	// If `sub` is bigger than `sequence`, then no match will be found
	if (sub.length() > sequence.length())
		return -1;
	
	string buffer = "";

	for (unsigned long i = start; i <= end; i++) {
		// TODO: Search, save in a buffer
		try {
			buffer = sequence.substr(i, sub.length());
			if (sub == buffer)
				return i;
		} catch (const std::out_of_range& exception) {
			// Catch from `substr` if the number of characters to take is too
			// big, in which case the search ends
			break;
		}
	}

	return -1;
}
