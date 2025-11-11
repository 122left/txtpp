#include <txtpp/simple_rule.hpp>

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

}