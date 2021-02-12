#pragma once
#include <zlib.h>
#include <cstring>

#include "util.hpp"

namespace CompressedReader {
	/**
	 * @brief Read one line out of the given @p f.
	 * Source code inspired from https://stackoverflow.com/a/17880402/7347145 by
	 * mkluwe and pawel_j.
	 * @param f The file descriptor to read from.
	 * @return Return a string.
	 */
	string readline(gzFile f, unsigned int buffer_size = 4096);
};
