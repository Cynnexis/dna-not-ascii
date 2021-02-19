#include "dna_allocator.hpp"
#include "ribosome.hpp"
#include <Stopwatch.h>

using namespace std;

int main(int argc, char* argv[]) {
	Stopwatch swatch = Stopwatch();
	swatch.set_mode(StopwatchMode::REAL_TIME);
	swatch.start("1");
	const string content = read_ensembl_file("data/Homo_sapiens.GRCh38.dna.chromosome.1.fa.gz", false,
#ifdef DEBUG
		500
#else
		-1
#endif
	);
	swatch.stop("1");

	cout << "Number of collected nucleotides: " << content.length() << endl;
	cout << content.substr(0, 60) << "..." << endl;

#ifdef DEBUG
	cout << "Total time for loading the chromosome 1: " << swatch.get_total_time("1") << "s" << endl;
#endif

	cout << "Computing the number of amino acid..." << endl;
	std::vector<AminoAcid::AminoAcidEnum> aminos = Ribosome::translate(content);
	
	// Use a map for building stats: The keys are the aminos acid, the values are their occurrences in the chromosome
	std::map<AminoAcid::AminoAcidEnum, unsigned long> occurrences;
	for (int i = AminoAcid::first; i < AminoAcid::last; i++)
		occurrences[static_cast<AminoAcid::AminoAcidEnum>(i)] = 0;
	
	// Count the occurrences
	for (const AminoAcid::AminoAcidEnum& a : aminos)
		occurrences[a]++;

	// Print stats
	for (const auto& [key, value] : occurrences)
		cout << "\t" << AminoAcid::to_string(key) << ": " << value << endl;

	return 0;
}
