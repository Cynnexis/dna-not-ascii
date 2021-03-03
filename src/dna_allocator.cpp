#include "dna_allocator.hpp"

string read_ensembl_file(const string& filepath, bool include_unknown_nucleotide, int printEveryMs) {
	// Read the file stat
	struct stat fileStat;
	if (stat(filepath.c_str(), &fileStat) != 0)
		// Throw an exception if an error occurred
		throw std::runtime_error(std::strerror(errno));

	int numReadBytes = 0;
	time_t lastPrint = 0;
	ProgressBar progressBar(fileStat.st_size, "Reading genome from file", cout);
	std::function<void(unsigned int, char*)> functor = [&](unsigned int iteration, char* buffer) -> void {
		numReadBytes += DEFAULT_GZ_BUFFER_LENGTH;

		// Update progress bar
		unsigned long current = epochMs();
		if (printEveryMs > 0 && lastPrint + printEveryMs <= current) {
			lastPrint = current;
			progressBar.Progressed(numReadBytes);
		}
	};
	string s = CompressedReader::read(filepath, DEFAULT_GZ_BUFFER_LENGTH, functor);

	// Remove first line
	size_t pos_end_first_line = s.find('\n');
	s = s.substr(pos_end_first_line + 1);

	// Remove all '\n'
	boost::algorithm::erase_all(s, "\n");
	
	// Finish the progress bar
	if (printEveryMs > 0) {
		progressBar.Progressed(fileStat.st_size);
		cout << endl;
	}

	if (printEveryMs > 0) {
		cout.precision(2);
		cout << "\nRead " << numReadBytes << " bytes out of the " << fileStat.st_size << " bytes file (" << numReadBytes / ((double) fileStat.st_size) * 100.0 << "%)" << endl;
	}

	return s;
}
