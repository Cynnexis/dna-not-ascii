#pragma once
#include <boost/algorithm/string.hpp>

#include "compressed_reader.hpp"

string read_ensembl_file(const string& filepath, bool verbose = true);
