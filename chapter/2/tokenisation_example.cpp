#include <txtpp/simple_rule.hpp>
#include <iostream>

int main() {
	const std::string sample = "in order to understand the world like O'saa, it is 'desired' to do' as the world does";

	txtpp::RuleTokeniser tokeniser;

	const std::vector<std::string> tokens = tokeniser.tokenise(sample);

	std::cout << "Original string: " << sample << '\n';

	std::cout << "Tokens:\n";

	for (const auto& token : tokens) {
		std::cout << token << '\n';
	}

	return EXIT_SUCCESS;
}