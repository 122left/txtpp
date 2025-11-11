/*
txtpp Basic Library
*/

#pragma once

#include <string>

namespace txtpp {

/// <summary>
/// Checks if a given character is a vowel
/// </summary>
/// <param name="c">The input character to be assessed for its vowel nature</param>
/// <returns>Boolean signifying if the input character is a vowel</returns>
bool is_vowel(const char c);

/// <summary>
/// Converts all the characters in a string to lower case in-place
/// </summary>
/// <param name="str">Mutable string to be converted to lower case</param>
void to_lower(std::string& str);

/// <summary>
/// Constructs a new string with all alphabetic characters converted to lower case
/// </summary>
/// <param name="str">Constant input string to be converted to lower case</param>
/// <returns>A string with all characters from the input converted to lower case</returns>
std::string to_lower(const std::string& str);

/// <summary>
/// Checks if a provided string represents a number
/// </summary>
bool is_number(const std::string& str);

/// <summary>
/// Roughly estimates if a provided string resembles an acronym (for example: A.D or J.E.)
/// </summary>
bool like_acronym(const std::string& str);
}