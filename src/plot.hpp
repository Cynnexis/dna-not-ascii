#pragma once
#include <pngwriter.h>
#include <cmath>
#include <map>
#include <tuple>
#include <progress_bar.hpp>

#include "util.hpp"

#define NUCLEOTIDE_PIXEL_WIDTH 5
#define NUCLEOTIDE_PIXEL_HEIGHT 5

namespace plot {
	typedef std::tuple<int, int, int> icolor;
	typedef std::tuple<double, double, double> dcolor;
	typedef std::map<char, icolor> map_nucleotide_icolor;
	typedef std::map<char, dcolor> map_nucleotide_dcolor;

	const map_nucleotide_dcolor default_colormap{
		{'A', std::make_tuple<double, double, double>(1., 0., 0.)},
		{'T', std::make_tuple<double, double, double>(1., 1., 0.)},
		{'C', std::make_tuple<double, double, double>(0., 1., 0.)},
		{'G', std::make_tuple<double, double, double>(0., 0., 1.)},
		{'N', std::make_tuple<double, double, double>(0., 0., 0.)},
	};

	/**
	 * @brief Write the given DNA sequence in a PNG image on the disk.
	 * 
	 * @param sequence The DNA sequence to write.
	 * @param filepath The path to the image on the disk.
	 * @param width When creating the image, the sequence is split into smaller
	 * pieces of length @p width. All those pieces appears then as rows on the
	 * images, forming a color matrix. Default to
	 * `ceil(sqrt(sequence.length()))`
	 * @param printEveryMs The number of milliseconds between two prints for
	 * indicating reading progression. Set it to a negative or null value to
	 * disable outputs. Defaults to -1.
	 */
	void dna_to_image(const string& sequence, string filepath, long width = -1, const map_nucleotide_dcolor colormap = default_colormap, int printEveryMs = 1);
}
