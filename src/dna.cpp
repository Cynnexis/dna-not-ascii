#include "dna_allocator.hpp"
#include <Stopwatch.h>

using namespace std;

int main(int argc, char* argv[]) {
	Stopwatch swatch = Stopwatch();
	swatch.set_mode(StopwatchMode::REAL_TIME);
	swatch.start("1");
	const string content = read_ensembl_file("data/Homo_sapiens.GRCh38.dna.chromosome.1.fa.gz", false);
	swatch.stop("1");

	cout << "Number of collected nucleotides: " << content.length() << endl;
	cout << content.substr(0, 60) << "..." << endl;

#ifdef DEBUG
	cout << "Total time for loading the chromosome 1: " << swatch.get_total_time("1") << "s" << endl;
#endif

	return 0;
}
