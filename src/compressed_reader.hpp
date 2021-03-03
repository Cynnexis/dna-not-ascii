#pragma once
#include <zlib.h>
#include <cstring>
#include <functional>

#include "util.hpp"

#define DEFAULT_GZ_BUFFER_LENGTH 4096

namespace CompressedReader {
	/**
	 * @brief Read one line out of the given @p f.
	 * @details Source code inspired from https://stackoverflow.com/a/17880402/7347145 by
	 * mkluwe and pawel_j.
	 * @param f The file descriptor to read from.
	 * @return Return a string.
	 */
	string readline(gzFile f, unsigned int buffer_size = DEFAULT_GZ_BUFFER_LENGTH);

	/**
	 * @brief Read and decompress the whole file.
	 * 
	 * @param f The file to read.
	 * @param buffer_size The size of the buffer. It will be used as batch size.
	 * @param callback You may specify a callback that will be invoked during
	 * the reading. It takes in argument the current iteration as an unsigned
	 * integer, and the value of the buffer. Note that the pointer to the buffer
	 * is sent, so you may change it in your callback to alter the final output.
	 * @return Return the content of the file as a string. Its length can be
	 * greater than the @p buffer_size.
	 */
	string read(gzFile f, unsigned int buffer_size = DEFAULT_GZ_BUFFER_LENGTH, std::function<void(unsigned int, char*)> callback = {});

	/**
	 * @brief Read and decompress the whole file.
	 * 
	 * @param filepath The path to the file to read.
	 * @param buffer_size The size of the buffer. It will be used as batch size.
	 * @param callback You may specify a callback that will be invoked during
	 * the reading. It takes in argument the current iteration as an unsigned
	 * integer, and the value of the buffer. Note that the pointer to the buffer
	 * is sent, so you may change it in your callback to alter the final output.
	 * @return Return the content of the file as a string. Its length can be
	 * greater than the @p buffer_size.
	 */
	string read(string filepath, unsigned int buffer_size = DEFAULT_GZ_BUFFER_LENGTH, std::function<void(unsigned int, char*)> callback = {});
};
