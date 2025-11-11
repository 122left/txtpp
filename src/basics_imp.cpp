#include <txtpp/basic.hpp>

#include <unordered_set>
#include <cctype>

namespace txtpp {

static constexpr unsigned int vowel_mask = (1 << ('a' & 31)) + (1 << ('e' & 31)) + (1 << ('i' & 31)) +
	(1 << ('o' & 31)) + (1 << ('u' & 31));

bool is_vowel(const char c) {
	return (vowel_mask >> (std::tolower(c) & 31)) & 1;
}

void to_lower(std::string& str) {
	for (char& c : str) c = std::tolower(c);
}

std::string to_lower(const std::string& str) {
	std::string res = str;
	to_lower(res);
	return res;
}

bool is_number(const std::string& str) {
	if (str.empty()) return true;
	size_t i = 0;
	if (str[0] == '-' && str.length() > 1) i = 1;
	for (; i < str.length(); i++) if (!std::isdigit(str[i])) return false;
	return true;
}

bool like_acronym(const std::string& str) { // ideally: https://www.writerswrite.co.za/seven-rules-for-acronyms/

	if (str.empty()) return false;
	const std::unordered_set<char> separators = {'-', '.', '_'};

	bool last_char_was_a_separator = false;
	bool separator_exists = false;
	bool fully_alphabetical = true;
	int case_consistency = 0;

	for (const char c : str) {
		if (std::isalpha(c)) {

			if (std::isupper(c)) {
				if (case_consistency == 0) case_consistency = 1;
				else if (case_consistency == -1 || case_consistency == 2) case_consistency = -2;
			}
			else {
				if (case_consistency == 0) case_consistency = -1;
				else if (case_consistency == 1) case_consistency = 2; // leaning: for ex. B.Sc.
			}

			last_char_was_a_separator = false;
		}
		else {
			fully_alphabetical = false;

			if (separators.contains(c)) {
				separator_exists = true;

				if (last_char_was_a_separator) return false;

				last_char_was_a_separator = true;
			}
		}
	}

	return (case_consistency == 1 && fully_alphabetical) ||
		((std::abs(case_consistency) == 1 || case_consistency > 1) && separator_exists);
} // there is room for improvement.

}