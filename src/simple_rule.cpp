#include <txtpp/simple_rule.hpp>

#include <unordered_set>

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
	std::unordered_set<std::string> res;

	auto curr_pos = input.begin();
	bool intQuoteFlag = false;
	
	const std::unordered_set<char> delim_set = {
		',', '.', '?', ':', ';', '!', '(', ')', '<', '>', '+', '*', '/', '^', '%', '\n', '\t',
		'|', '\'', '\"'
	};
	const std::unordered_set<char> ws = { '\t', '\n', ' ' };

	while (curr_pos != input.end()) { // buggy part
		auto cursor = curr_pos;
		L2:
		while (cursor != input.end() && delim_set.find(*cursor) == delim_set.end()) cursor++;

		if (cursor == input.end() && cursor == curr_pos) break;

		const char ch = (cursor != input.end()) ? *cursor : '@';

		if (ws.find(ch) != ws.end()) {
			if (curr_pos == cursor) {
				curr_pos++;
			}
			else {
				const std::string token = std::string(curr_pos, std::prev(cursor));
				curr_pos = std::next(cursor);
				res.insert(token);
			}
			continue;
		}

		if (ch == '\'') {
			if (delim_set.find(*std::prev(cursor)) != delim_set.end()) {
				intQuoteFlag = true;
				curr_pos++;
				continue;
			}

			if (delim_set.find(*std::next(cursor)) == delim_set.end()) {
				cursor++;
				goto L2;
			}
			else if (intQuoteFlag) {
				const std::string token = std::string(curr_pos, std::prev(cursor));
				intQuoteFlag = false;
				res.insert(token);
			}
			else {
				const std::string token = std::string(curr_pos, cursor);
				res.insert(token);
			}

			continue;
		}

		if (cursor == curr_pos) {
			const std::string token = "" + ch;
			curr_pos = std::next(cursor);
			res.insert(token);
		}
		else {
			const std::string token = std::string(curr_pos, std::prev(cursor));
			curr_pos = cursor;
			res.insert(token);
		}
	}

	return std::vector<std::string>(res.begin(), res.end());
}

}