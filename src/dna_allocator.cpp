#include "dna_allocator.hpp"

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

	ProgressBar progressBar(fileStat.st_size, "Reading genome from file", cout);
	for (unsigned int i = 0;; i++) {
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

		// Update progress bar
		unsigned long current = epochMs();
		if (printEveryMs > 0 && lastPrint + printEveryMs <= current) {
			lastPrint = current;
			progressBar.Progressed(numReadChars / sizeof(int));
		}
	}
	// Finish the progress bar
	if (printEveryMs > 0) {
		progressBar.Progressed(fileStat.st_size);
		cout << endl;
	}

	if (printEveryMs > 0) {
		cout.precision(2);
		cout << "\nRead " << numReadChars / sizeof(int) << " bytes out of the " << fileStat.st_size << " bytes file (" << (numReadChars / sizeof(int)) / ((double) fileStat.st_size) * 100.0 << "%)" << endl;
	}

	return s;
}
