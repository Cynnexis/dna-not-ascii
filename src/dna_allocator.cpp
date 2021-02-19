#include "dna_allocator.hpp"

/**
 * @brief Get the current epoch in milliseconds.
 * @details Source code inspired from https://stackoverflow.com/a/17371925/7347145
 * by Dan Moulding and Raedwald.
 * 
 * @return unsigned long The time in milliseconds starting from January the 1st,
 * 1970.
 */
unsigned long epochMs() {
	struct timespec spec;
	clock_gettime(CLOCK_REALTIME, &spec);
	return spec.tv_sec * 1000L + (spec.tv_nsec / 1.0e6);
}

string read_ensembl_file(const string& filepath, bool include_unknown_nucleotide, int printEveryMs) {
	// Read the file stat
	struct stat fileStat;
	if (stat(filepath.c_str(), &fileStat) != 0)
		// Throw an exception if an error occurred
		throw std::runtime_error(std::strerror(errno));

	gzFile f = gzopen(filepath.c_str(), "rb");
	int numReadChars = 0;
	time_t lastPrint = 0;
	string s = "";

	for (unsigned int i = 0;; i++) {
		unsigned long current = epochMs();
		if (printEveryMs > 0 && lastPrint + printEveryMs <= current) {
			lastPrint = current;
			cout << "Collected " << i << " lines.\r" << std::flush;
		}
		
		const string line = CompressedReader::readline(f, 80);
		if (line.empty())
			break;
		
		numReadChars += line.length();

		// Ignore the first line
		if (i > 0) {
			// Keep only valid nucleotides
			string nucleotides = "";
			for (const char& nucleotide : line) {
				if (nucleotide == 'A' || nucleotide == 'T' || nucleotide == 'C' || nucleotide == 'G' || include_unknown_nucleotide && nucleotide == 'N')
					s += nucleotide;
			}
		}
	}

	if (printEveryMs > 0)
		cout << "\nRead " << numReadChars / sizeof(int) << " bytes out of the " << fileStat.st_size << " bytes file (" << (numReadChars / sizeof(int)) / ((double) fileStat.st_size) * 100.0 << "%)" << endl;

	return s;
}
