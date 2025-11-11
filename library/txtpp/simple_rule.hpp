#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace txtpp {

class RuleClassifier {

public:

	/// <summary>
	/// classify() is a basic rule-based classifier that accepts a query string, and a spreadsheet being a vector of vectors of type string -- where the last column would be assumed to be the class label.
	/// </summary>
	static std::string classify(const std::string& query, const std::vector<std::vector<std::string>>& ss);

	/// <summary>
	/// Overload for classify() where `id` is the column containing the class label (0-indexed).
	/// </summary>
	static std::string classify(const std::string& query, const std::vector<std::vector<std::string>>& ss, const size_t id);
};

class RuleTokeniser {

public:

	/// <summary>
	/// Tokenises a string into unique constituent tokens.
	/// </summary>
	/// <param name="input">Input string to be tokenised</param>
	/// <returns>Returns a vector of unique tokens</returns>
	static std::vector<std::string> tokenise(const std::string& input);
};

class RuleStemmer {

public:

	/// <summary>
	/// Inflectionally stems a single token via an accompanying dictionary.
	/// </summary>
	/// <param name="token">String representing a token to be stemmed</param>
	/// <param name="dict">An unordered_map<string,string> representing a dictionary</param>
	/// <returns>A string containing the stemmed text</returns>
	static std::string inflectional_stem(const std::string& token, std::unordered_map<std::string, std::string>& dict);
};

}