#include "ribosome.hpp"

Ribosome::TranslationException::TranslationException(const string& nucleotides, int position) noexcept : std::runtime_error("Couldn't translate the given codon.") {
	if (nucleotides.length() < 80)
		this->nucleotides = nucleotides;
	
	this->pos = position;
}

const char* Ribosome::TranslationException::what() const noexcept {
	string s = string("Couldn't translate the ");
	if (nucleotides.length() > 0)
		s += "codon \"" + nucleotides + "\"";
	else
		s += "given codon";

	if (pos >= 0)
		s += " at position " + std::to_string(pos);
	
	s += ".";
	
	return s.c_str();
}

bool Ribosome::checkNucleotides(const char& nucleotide, bool allow_n) noexcept {
	return nucleotide == 'A' || nucleotide == 'C' || nucleotide == 'G' || nucleotide == 'T' || allow_n && nucleotide == 'N';
}

AminoAcid::AminoAcidEnum Ribosome::translate_codon(const char& nucleotide_1, const char& nucleotide_2, const char& nucleotide_3) {
	// Check given characters (A/C/T/G)
	if (!checkNucleotides(nucleotide_1))
		throw std::runtime_error("The first nucleotide is not valid: " + string(&nucleotide_1));
	if (!checkNucleotides(nucleotide_2))
		throw std::runtime_error("The second nucleotide is not valid: " + string(&nucleotide_2));
	if (!checkNucleotides(nucleotide_3))
		throw std::runtime_error("The third nucleotide is not valid: " + string(&nucleotide_3));

	if (nucleotide_1 == 'A') {
		if (nucleotide_2 == 'A') {
			if (nucleotide_3 == 'A' || nucleotide_3 == 'G')
				return AminoAcid::AminoAcidEnum::Lys;
			else // The last nucleotide is T or C
				return AminoAcid::AminoAcidEnum::Asn;
		} else if (nucleotide_2 == 'T') {
			if (nucleotide_3 == 'G')
				// The Methionine is also the starting cordon
				return AminoAcid::AminoAcidEnum::Met;
			else // The last nucleotide is A, T or C
				return AminoAcid::AminoAcidEnum::Ile;
		} else if (nucleotide_2 == 'C') {
			// Always return Threonine
			return AminoAcid::AminoAcidEnum::Thr;
		} else { // The second nucleotide is G
			if (nucleotide_3 == 'A' || nucleotide_3 == 'G')
				return AminoAcid::AminoAcidEnum::Arg;
			else // The last nucleotide is T or C
				return AminoAcid::AminoAcidEnum::Ser;
		}
	} else if (nucleotide_1 == 'T') {
		if (nucleotide_2 == 'A') {
			if (nucleotide_3 == 'A' || nucleotide_3 == 'G')
				return AminoAcid::AminoAcidEnum::Stop;
			else // The last nucleotide is T or C
				return AminoAcid::AminoAcidEnum::Tyr;
		} else if (nucleotide_2 == 'T') {
			if (nucleotide_3 == 'A' || nucleotide_3 == 'G')
				return AminoAcid::AminoAcidEnum::Leu;
			else // The last nucleotide is T or C
				return AminoAcid::AminoAcidEnum::Phe;
		} else if (nucleotide_2 == 'C') {
			// Always return Serine
			return AminoAcid::AminoAcidEnum::Ser;
		} else { // The second nucleotide is G
			if (nucleotide_3 == 'T' || nucleotide_3 == 'C')
				return AminoAcid::AminoAcidEnum::Cys;
			else if (nucleotide_3 == 'A')
				return AminoAcid::AminoAcidEnum::Stop;
			else // The last nucleotide is G
				return AminoAcid::AminoAcidEnum::Trp;
		}
	} else if (nucleotide_1 == 'C') {
		if (nucleotide_2 == 'A') {
			if (nucleotide_3 == 'A' || nucleotide_3 == 'G')
				return AminoAcid::AminoAcidEnum::Gln;
			else // The last nucleotide is T or C
				return AminoAcid::AminoAcidEnum::His;
		} else if (nucleotide_2 == 'T') {
			// Always return Leucine
			return AminoAcid::AminoAcidEnum::Leu;
		} else if (nucleotide_2 == 'C') {
			// Always return Proline
			return AminoAcid::AminoAcidEnum::Pro;
		} else { // The second nucleotide is G
			// Always return Arginine
			return AminoAcid::AminoAcidEnum::Arg;
		}
	} else if (nucleotide_1 == 'G') {
		if (nucleotide_2 == 'A') {
			if (nucleotide_3 == 'A' || nucleotide_3 == 'G')
				return AminoAcid::AminoAcidEnum::Glu;
			else // The last nucleotide is T or C
				return AminoAcid::AminoAcidEnum::Asp;
		} else if (nucleotide_2 == 'T') {
			// Always return Valine
			return AminoAcid::AminoAcidEnum::Val;
		} else if (nucleotide_2 == 'C') {
			// Always return Alanine
			return AminoAcid::AminoAcidEnum::Ala;
		} else { // The second nucleotide is G
			// Always return Glycine
			return AminoAcid::AminoAcidEnum::Gly;
		}
	} else
		throw TranslationException(string(&nucleotide_1) + string(&nucleotide_2) + string(&nucleotide_3));
}
AminoAcid::AminoAcidEnum Ribosome::translate_codon(const string& codon) {
	if (codon.length() != MAX_NUCLEOTIDES_HANDLING)
		throw std::runtime_error("Expected codon of length 3, got length " + std::to_string(codon.length()));
	
	return translate_codon(codon[0], codon[1], codon[2]);
}

std::vector<AminoAcid::AminoAcidEnum> Ribosome::translate(const string& sequence, int printEveryMs) {
	std::vector<AminoAcid::AminoAcidEnum> results;
	results.reserve(lround(sequence.length() / ((double) MAX_NUCLEOTIDES_HANDLING)));

	char buffer[MAX_NUCLEOTIDES_HANDLING] = {0, 0, 0};
	short currentBufferIndex = 0;

	ProgressBar progressBar((int) (sequence.length() - 1), "Translating codons", cout);
	time_t lastPrint = 0;
	for (int i = 0; i < sequence.length(); i++) {
		// If the buffer is not full...
		if (currentBufferIndex < MAX_NUCLEOTIDES_HANDLING) {
			// Fill the buffer (if it is a valid nucleotide)
			if (checkNucleotides(sequence[i], false))
				buffer[currentBufferIndex++] = sequence[i];
		}
		// If the buffer is full...
		else {
			// Translate the buffer
			results.push_back(Ribosome::translate_codon(buffer[0], buffer[1], buffer[2]));
			// Reset the buffer
			currentBufferIndex = 0;
		}

		// Update progress bar
		unsigned long current = epochMs();
		if (printEveryMs > 0 && lastPrint + printEveryMs <= current) {
			lastPrint = current;
			progressBar.Progressed((int) i);
		}
	}
	if (printEveryMs > 0) {
		progressBar.Progressed((int) (sequence.length() - 1));
		cout << endl;
	}

	return results;
}
