#pragma once
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <cmath>
#include <cerrno>
#include <boost/algorithm/string.hpp>

#include "compressed_reader.hpp"

/**
 * @brief Read the given file and return the DNA sequence.
 * @details Read the given FASTA file compressed using the GZ algorithm, and
 * return only the DNA sequence as a string containing either the characters
 * 'A', 'T', 'C' and 'G' (and 'N' if @p include_unknown_nucleotide is `true`).
 * 
 * @param filepath The path to the file to read.
 * @param include_unknown_nucleotide If `true`, include in the returned string
 * the characters 'N' in the given file, meaning that the nucleotide at the
 * index position is not a valid nucleotide. Defaults to `false`.
 * @param printEveryMs The number of milliseconds between two prints for
 * indicating reading progression. Set it to a negative or null value to disable
 * outputs. Defaults to -1.
 * @return Returns the content of the file. Only the characters 'A', 'T', 'C'
 * and 'G' (and 'N' if @p include_unknown_nucleotide is `true`) will be in this
 * string. The first line of the file containing meta-data is ignored, as well
 * as other characters in the sequence that are not describing a nucleotide.
 */
string read_ensembl_file(const string& filepath, bool include_unknown_nucleotide = false, int printEveryMs = -1);
