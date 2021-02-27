#include "plot.hpp"

std::map<char, std::tuple<double, double, double>> colormap{
	{'A', std::make_tuple<double, double, double>(1., 0., 0.)},
	{'T', std::make_tuple<double, double, double>(1., 1., 0.)},
	{'C', std::make_tuple<double, double, double>(0., 1., 0.)},
	{'G', std::make_tuple<double, double, double>(0., 0., 1.)},
	{'N', std::make_tuple<double, double, double>(0., 0., 0.)},
};

void plot::dna_to_image(const string& sequence, string filepath, long width, int printEveryMs) {
	if (width <= 0)
		width = (long) ceil(sqrt((long double) sequence.length()));

	unsigned long height = ceil(((long double) sequence.length()) / width);

	unsigned int width_px = width * NUCLEOTIDE_PIXEL_WIDTH;
	unsigned int height_px = height * NUCLEOTIDE_PIXEL_HEIGHT;

	cout << "Creating an image of " << width_px << "x" << height_px << "px..." << endl;
	pngwriter img(width_px, height_px, 65535, filepath.c_str());

	ProgressBar progress((int) (sequence.length() - 1), "Saving DNA as image", cout);
	time_t lastPrint = 0;
	for (int i = 0; i < sequence.length(); i++) {
		unsigned int col = i % width;
		unsigned int row = ceil(i / width);

		unsigned int col_px = col * NUCLEOTIDE_PIXEL_WIDTH + 1;
		unsigned int row_px = ((height - 1) * NUCLEOTIDE_PIXEL_HEIGHT) - row * NUCLEOTIDE_PIXEL_HEIGHT + 1;

		img.filledsquare(col_px, row_px, col_px + NUCLEOTIDE_PIXEL_WIDTH, row_px + NUCLEOTIDE_PIXEL_HEIGHT, std::get<0, double>(colormap[sequence[i]]), std::get<1, double>(colormap[sequence[i]]), std::get<2, double>(colormap[sequence[i]]));

		// Update progress bar
		unsigned long current = epochMs();
		if (printEveryMs > 0 && lastPrint + printEveryMs <= current) {
			lastPrint = current;
			progress.Progressed((int) i);
		}
	}
	if (printEveryMs > 0) {
		progress.Progressed((int) (sequence.length() - 1));
		cout << endl;
	}

	img.close();
}
