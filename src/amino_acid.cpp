#include "amino_acid.hpp"

string AminoAcid::to_string(const AminoAcidEnum& amino) {
	switch (amino) {
		case Stop:
			return "STOP";
		case Ala:
			return "Alanine";
		case Arg:
			return "Arginine";
		case Asn:
			return "Asparagine";
		case Asp:
			return "Aspartic acid";
		case Cys:
			return "Cysteine";
		case Glu:
			return "Glutamic acid";
		case Gln:
			return "Glutamine";
		case Gly:
			return "Glycine";
		case His:
			return "Histidine";
		case Ile:
			return "Isoleucine";
		case Leu:
			return "Leucine";
		case Lys:
			return "Lysine";
		case Met:
			return "Methionine";
		case Phe:
			return "Phenylalanine";
		case Pro:
			return "Proline";
		case Ser:
			return "Serine";
		case Thr:
			return "Threonine";
		case Trp:
			return "Tryptophan";
		case Tyr:
			return "Tyrosine";
		case Val:
			return "Valine";
		default:
			throw std::runtime_error("Invalid amino acid.: " + std::to_string(amino));
	}
}
