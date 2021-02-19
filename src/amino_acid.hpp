#pragma once

#include "util.hpp"

namespace AminoAcid {
	enum AminoAcidEnum {
		Stop = -1,
		Ala,
		Arg,
		Asn,
		Asp,
		Cys,
		Glu,
		Gln,
		Gly,
		His,
		Ile,
		Leu,
		Lys,
		Met, // Also the starting cordon
		Phe,
		Pro,
		Ser,
		Thr,
		Trp,
		Tyr,
		Val,
	};

	const int first = AminoAcidEnum::Stop;
	const int last = AminoAcidEnum::Val;

	string to_string(const AminoAcidEnum& amino);
}
