#include "compressed_reader.hpp"

string CompressedReader::readline(gzFile f, unsigned int buffer_size) {
	std::vector<char> v(buffer_size);
	unsigned int pos = 0;
	while (true) {
		// Check if there is an error
		if (gzgets(f, &v[pos], v.size() - pos) == 0) {
			// end-of-file or error
			int err;
			const char* msg = gzerror(f, &err);
			if (err != Z_OK)
				throw std::runtime_error("An error occurred while reading a compressed file: " + string(msg));
			break;
		}
		unsigned int read = std::strlen(&v[pos]);
		if (v[pos + read - 1] == '\n') {
			if (pos + read >= 2 && v[pos + read - 2] == '\r') {
				pos = pos + read - 2;
			} else {
				pos = pos + read - 1;
			}
			break;
		}
		if (read == 0 || pos + read < v.size() - 1) {
			pos = read + pos;
			break;
		}
		pos = v.size() - 1;
		v.resize(v.size() * 2);
	}

	if (v.empty())
		throw std::runtime_error("Empty gz file");

	v.resize(pos);
	return std::string(v.begin(), v.end());
}
