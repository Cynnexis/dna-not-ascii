#include "dna_allocator.hpp"

string read_ensembl_file(const string& filepath, bool verbose) {
	gzFile f = gzopen(filepath.c_str(), "rb");
	string s = "";

	for (unsigned int i = 0;; i++) {
		if (verbose && i % 10000 == 0) {
			cout << "Collected " << i << " lines.\r" << std::flush;
		}
		
		const string line = CompressedReader::readline(f, 80);
		if (line.empty())
			break;
		
		// Ignore the first line
		if (i > 0) {
			// Keep only valid nucleotides
			string nucleotides = "";
			for (const char& nucleotide : line) {
				if (nucleotide == 'A' || nucleotide == 'T' || nucleotide == 'C' || nucleotide == 'G')
					s += nucleotide;
			}
		}
	}
	return s;
}
