#pragma once
#include <cmath>
#include "amino_acid.hpp"

#define MAX_NUCLEOTIDES_HANDLING 3

namespace Ribosome {
	/**
	 * @brief Excpetion that is thrown when a ribosome translation error
	 * occurred.
	 */
	class TranslationException : public std::runtime_error {
		private:
		string nucleotides = "";
		int pos = -1;

		public:
		/**
		 * @brief Construct a new Translation Exception object.
		 * 
		 * @param nucleotides The sequence of nucleotides that caused the error.
		 * Please be specific, and do NOT put the whole DNA sequence. If the
		 * string is empty or has a length greater than 80, the parameter will
		 * be ignored and the error message will be adapted. Defaults to an
		 * empty string.
		 * @param position The position of the codon in the sequence. If not
		 * given or its value is -1, the error message will be adapted. Defaults
		 * to -1.
		 */
		explicit TranslationException(const string& nucleotides = "", int position = -1) noexcept;

		/**
		 * @brief Construct the error message.
		 * @return const char* The error message.
		 */
		virtual const char* what() const noexcept;
	};

	bool checkNucleotides(const char& nucleotide, bool allow_n = false) noexcept;

	/**
	 * @brief Translate three nucleotides into an @ref AminoAcidEnum.
	 * @details Search for the @ref AminoAcidEnum associated to the codon
	 * @p nucleotide_1, @p nucleotide_2 and @p nucleotide_3 (in this specific
	 * order). If no associated @ref AminoAcidEnum exists, 
	 * 
	 * @param nucleotide_1 The first nucleotide. It must be either A, C, G or T.
	 * @param nucleotide_2 The second nucleotide. It must be either A, C, G or
	 * T.
	 * @param nucleotide_3 The third nucleotide. It must be either A, C, G or T.
	 * @return Returns the associated @ref AminoAcidEnum if found.
	 * @exception TranslationException Thrown when the given codon cannot be
	 * translated into a @ref AminoAcidEnum.
	 * @exception runtime_error Thrown when the given codon contains invalid
	 * characters.
	 */
	AminoAcid::AminoAcidEnum translate_codon(const char& nucleotide_1, const char& nucleotide_2, const char& nucleotide_3);

	/**
	 * @brief Translate three nucleotides into an @ref AminoAcidEnum.
	 * @details Search for the @ref AminoAcidEnum associated to the codon
	 * @p nucleotide_1, @p nucleotide_2 and @p nucleotide_3 (in this specific
	 * order). If no associated @ref AminoAcidEnum exists, 
	 * 
	 * @param codon The codon of DNA to translate. It must be 3 characters long.
	 * @return Returns the associated @ref AminoAcidEnum if found.
	 * @exception TranslationException Thrown when the given codon cannot be
	 * translated into a @ref AminoAcidEnum.
	 * @exception runtime_error Thrown when the given doesn't contain exactly
	 * 3 nucleotides, or contains invalid characters.
	 */
	AminoAcid::AminoAcidEnum translate_codon(const string& codon);

	std::vector<AminoAcid::AminoAcidEnum> translate(const string& sequence);
}
