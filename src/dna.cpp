#include "dna_allocator.hpp"
#include "ribosome.hpp"
#include "algo_gen.hpp"
#include "plot.hpp"
#include <Stopwatch.h>

using namespace std;

#define PRINT_FREQUENCY_MS 50

int main(int argc, char* argv[]) {
	Stopwatch swatch = Stopwatch();
	swatch.set_mode(StopwatchMode::REAL_TIME);
	swatch.start("1");
	const string content = read_ensembl_file("data/Homo_sapiens.GRCh38.dna.chromosome.MT.fa.gz", true,
#ifdef DEBUG
		PRINT_FREQUENCY_MS
#else
		-1
#endif
	);
	swatch.stop("1");

	cout << "Number of collected nucleotides: " << content.length() << endl;
	cout << content.substr(10000, 60) << "..." << endl;

#ifdef DEBUG
	cout << "Total time for loading the chromosome 1: " << swatch.get_total_time("1") << "s" << endl;
#endif
	{
		ProgressBar progressBar((int) (content.length() - 1), "Computing the occurrences of each nucleotides", cout);
		// Use a map for building stats: The keys are the nucleotides, the
		// values are their occurrences in the chromosome
		std::map<char, unsigned long> occurrences;
		occurrences['A'] = 0;
		occurrences['T'] = 0;
		occurrences['C'] = 0;
		occurrences['G'] = 0;
		occurrences['N'] = 0;

		// Count occurrences
		time_t lastPrint = 0;
		for (unsigned long i = 0; i < content.length(); i++) {
			occurrences[content[i]] += 1;
			
			// Update progress bar
			unsigned long current = epochMs();
			if (PRINT_FREQUENCY_MS > 0 && lastPrint + PRINT_FREQUENCY_MS <= current) {
				lastPrint = current;
				progressBar.Progressed((int) i);
			}
		}
		if (PRINT_FREQUENCY_MS > 0) {
			progressBar.Progressed((int) (content.length() - 1));
			cout << endl;
		}
		
		// Compute totals (with and without N's)
		unsigned long totalWithN = 0;
		for (const auto& [_, value] : occurrences)
			totalWithN += value;
		
		// Assert that `totalWithN` is equal to `content.length()`
		if (totalWithN != content.length())
			throw std::runtime_error("Counted a total of " + std::to_string(totalWithN) + " nucleotides, but the sequence actually contains " + std::to_string(content.length()) + ".");

		unsigned long totalWithoutN = totalWithN - occurrences['N'];

		// Print stats
		cout.precision(2);
		for (const auto& [key, value] : occurrences) {
			cout << "\tNumber of " << key << ": " << value << " (" << (((double) value) / totalWithN) * 100.0 << "%";
			if (key != 'N')
				cout << " with N, " << (((double) value) / totalWithoutN) * 100.0 << "% without";
			
			cout << ")" << endl;
		}
	}

	{
		std::vector<AminoAcid::AminoAcidEnum> aminos = Ribosome::translate(content, PRINT_FREQUENCY_MS);
		
		// Use a map for building stats: The keys are the aminos acid, the
		// values are their occurrences in the chromosome
		std::map<AminoAcid::AminoAcidEnum, unsigned long> occurrences;
		for (int i = AminoAcid::first; i < AminoAcid::last; i++)
			occurrences[static_cast<AminoAcid::AminoAcidEnum>(i)] = 0;
		
		// Count the occurrences
		ProgressBar progressBar((int) (content.length() - 1), "Computing the number of amino acid", cout);
		time_t lastPrint = 0;
		for (unsigned long i = 0; i < aminos.size(); i++) {
			occurrences[aminos[i]]++;

			// Update progress bar
			unsigned long current = epochMs();
			if (PRINT_FREQUENCY_MS > 0 && lastPrint + PRINT_FREQUENCY_MS <= current) {
				lastPrint = current;
				progressBar.Progressed((int) i);
			}
		}
		if (PRINT_FREQUENCY_MS > 0) {
			progressBar.Progressed((int) (content.length() - 1));
			cout << endl;
		}

		// Print stats
		for (const auto& [key, value] : occurrences)
			cout << "\t" << AminoAcid::to_string(key) << ": " << value << " (" << (((double) value) / aminos.size()) * 100.0 << "%)" << endl;
	}

	{
		ProgressBar progressBar((int) (content.length() - 1), "Searching proteins", cout);
		time_t lastPrint = 0;
		const string startingCodon = "ATG";
		unsigned long num_proteins = 0;
		unsigned long sum_protein_size = 0;
		unsigned long min_protein_size = ULONG_MAX;
		unsigned long max_protein_size = 0;
		unsigned long i = 0;
		while (true) {
			if (i >= content.length())
				break;

			size_t start = content.find(startingCodon, i);
			if (start < i || start >= content.length())
				break;
			
			size_t end = -1;
			try {
				for (unsigned long j = i + 3; j < content.length(); j += 3) {
					string codon = content.substr(j, 3);
					if (codon == "TAA" || codon == "TAG" || codon == "TGA") {
						end = j;
						break;
					}
				}
			} catch (const std::out_of_range& exception) {
				// Catch from `substr` if the number of characters to take is
				// too big, in which case the search ends
			}
			
			if (start < end && end < content.length()) {
				// Compute stats
				num_proteins++;
				unsigned long protein_size = end + 2 - start;
				sum_protein_size += protein_size;
				if (protein_size < min_protein_size)
					min_protein_size = protein_size;
				
				if (protein_size > max_protein_size)
					max_protein_size = protein_size;

				if (end + 3L <= i)
					throw std::runtime_error("Expected iteration to grow after detecting the end of protein and added 3, but got i=" + std::to_string(i) + " and end=" + std::to_string(end) + ".");
				i = end + 3L;
			} else {
				if (start + 1L <= i)
					throw std::runtime_error("Expected iteration to grow after failing to detect the end of protein and added 1 to the start, but got i=" + std::to_string(i) + " and start=" + std::to_string(start) + ".");
				i = start + 1L;
			}
			
			// Update progress bar
			unsigned long current = epochMs();
			if (PRINT_FREQUENCY_MS > 0 && lastPrint + PRINT_FREQUENCY_MS <= current) {
				lastPrint = current;
				progressBar.Progressed((int) i);
			}
		}
		if (PRINT_FREQUENCY_MS > 0) {
			progressBar.Progressed((int) (content.length() - 1));
			cout << endl;
		}

		cout.precision(2);
		cout << "\tNumber of proteins: " << num_proteins << "\n\tAverage protein size: " << ((long double) sum_protein_size) / num_proteins << " nucleotides\n\tMin protein size: " << min_protein_size << " nucleotides\n\tMax protein size: " << max_protein_size << " nucleotides" << endl;
	}

	// Save sequence as an image to disk
	plot::dna_to_image(content, "mt.png", -1, PRINT_FREQUENCY_MS);

	return 0;
}
