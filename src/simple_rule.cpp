#include <txtpp/simple_rule.hpp>

#include <txtpp/basic.hpp>

#include <unordered_set>
#include <set>

namespace txtpp {

// WIP
std::string RuleClassifier::classify(const std::string& query, const std::vector<std::vector<std::string>>& ss) {
	return "";
}

std::string RuleClassifier::classify(const std::string& query, const std::vector<std::vector<std::string>>& ss, const size_t id) {
	return "";
}
// WIP^^

std::vector<std::string> RuleTokeniser::tokenise(const std::string& input) {
	std::set<std::string> res;

	std::string::const_iterator curr_pos = input.begin();
	bool int_quote_flag = false;
	
	const std::unordered_set<char> delims = {
		',', '.', '?', ':', ';', '!', '(', ')', '<', '>', '+', '*', '/', '^', '%', '\n', '\t',
		'|', '\'', '\"', ' '
	};
	const std::unordered_set<char> ws = { '\t', '\n', ' ' };

	while (curr_pos != input.end()) {
		auto cursor = curr_pos;

		while (cursor != input.end() && !delims.contains(*cursor)) cursor++;

		std::string token;

		// to never forget: std::string(ite_1, ite_2) stops right before ite_2 in deep copy
		if (cursor == input.end() && cursor != curr_pos) {
			token = std::string(curr_pos, cursor);
			res.insert(token);
			break;
		}

		if (ws.contains(*cursor)) {
			if (cursor == curr_pos) {
				curr_pos++;
			}
			else {
				token = std::string(curr_pos, cursor);
				res.insert(token);
				curr_pos = std::next(cursor);
			}
			continue;
		}

		if (*cursor == '\'' || *cursor == '\"') {
			if (cursor == input.begin() || delims.contains(*std::prev(cursor))) {
				int_quote_flag = true;
				curr_pos++;
				continue;
			}
			if (std::next(cursor) == input.end() || delims.contains(*std::next(cursor))) {
				auto tmp = std::next(cursor);
				while (tmp != input.end() && delims.contains(*tmp)) tmp++;
				token = std::string(curr_pos, cursor);
				curr_pos = tmp;
			}
			else if (int_quote_flag) {
				int_quote_flag = false;
				token = std::string(curr_pos, cursor);
				curr_pos = std::next(cursor);
			}
			else {
				auto tmp = std::next(cursor);
				while (tmp != input.end() && !delims.contains(*tmp)) tmp++;
				cursor = std::prev(tmp);
				token = std::string(curr_pos, std::next(cursor));
				curr_pos = tmp;
				int_quote_flag = false;
			}
			res.insert(token);
			continue;
		}

		if (curr_pos == cursor && delims.contains(*cursor)) { // it causes issues otherwise...
			curr_pos++;
			continue;
		}
		token = (curr_pos == cursor) ? "" + *cursor : std::string(curr_pos, cursor);
		curr_pos = std::next(cursor);
		res.insert(token);
	}

	return std::vector(res.begin(), res.end());
}

/*
RuleStemmer implementation
*/


static void inplace_inflectional_stem(std::string& token, std::unordered_map<std::string, std::string>& dict) {
	
	const std::unordered_set<char> doubling_consonants = { 'b', 'd', 'g', 'k', 'm', 'n', 'p', 'r', 'l', 't' };

	if (token.length() < 4 ||
		is_number(token) ||
		like_acronym(token)
		) {
		return;
	}

	if (dict.contains(token)) {
		token = dict[token];
		return;
	}

	char y = token.back();
	char x = *std::next(token.rbegin());

	if ((x == '\'' && y == 's') || (x == 's' && y == '\'')) {
		token = token.substr(0, token.length() - 2);
		return;
	}

	if ((x == 'i' || x == 'u' || x == 's') && y == 's') {
		return;
	}

	if (y == 's') {
		int fac = (x == 'e') ? 2 : 1;
		const std::string tmp = token.substr(0, token.length() - fac);
		if (dict.contains(tmp)) {
			token = dict[tmp];
			return;
		}
	}

	char w = *std::next(std::next(token.rbegin()));

	if (w == 'i' && x == 'e' && y == 's') {
		token = token.substr(0, token.length() - 3) + 'y';
		return;
	}

	if (y == 's') {
		token = token.substr(0, token.length() - 1);
		return;
	}

	if (!((x == 'e' && y == 'd') || (w == 'i' && x == 'n' && y == 'g'))) return;

	if (token.ends_with("ed")) {
		const std::string tmp = token.substr(0, token.length() - 2);
		if (dict.contains(tmp)) {
			token = dict[tmp];
			return;
		}
	}

	if (token.ends_with("ied")) {
		token = token.substr(0, token.length() - 3) + 'y';
		return;
	}
	
	if (token.ends_with("eed")) {
		token = token.substr(0, token.length() - 1);
		if (dict.contains(token)) {
			return;
		}
	}
	else if (token.ends_with("ed")) {
		token = token.substr(0, token.length() - 2);
	}

	if (token.ends_with("ing")) {
		if (token.length() > 5) {
			token = token.substr(0, token.length() - 3);
			if (dict.contains(token)) {
				return;
			}
		}
		else {
			return;
		}
	}

	// no 'ed's or 'ing's now hopefully

	x = *std::next(token.rbegin());
	y = token.back();

	if (x == y && doubling_consonants.contains(x)) {
		const std::string tmp = token.substr(0, token.length() - 1);
		if (dict.contains(tmp)) {
			token = (x == 'l') ? token : dict[tmp];
			return;
		}
	}
	else {
		std::string tmp = token + 'e';
		if (dict.contains(tmp)) {
			token = dict[tmp];
			return;
		}
		if ((token.back() == 'c' || token.back() == 'z') ||
			((x == 'g' || x == 'l') && doubling_consonants.contains(y)) ||
			is_vowel(x) && !is_vowel(y)) {
			token += 'e';
			return;
		}
	}

	return;
}

std::string RuleStemmer::inflectional_stem(const std::string& token, std::unordered_map<std::string, std::string>& dict) {

	std::string res = token;

	inplace_inflectional_stem(res, dict);
	return res;
}


}