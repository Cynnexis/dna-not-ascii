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
	void dna_to_image(const string& sequence, string filepath, long width = -1, int printEveryMs = 1);
}
