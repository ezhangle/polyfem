#include <polyfem/StringUtils.hpp>
#include <iomanip>


// Split a string into tokens
std::vector<std::string> polyfem::StringUtils::split(const std::string &str, const std::string &delimiters) {
	// Skip delimiters at beginning.
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

	std::vector<std::string> tokens;
	while (std::string::npos != pos || std::string::npos != lastPos) {
		// Found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}

	return tokens;
}

// Skip comments in a stream
std::istream &polyfem::StringUtils::skip(std::istream &in, char x) {
	std::string dummy;
	while ((in >> std::ws).peek() ==
		std::char_traits<char>::to_int_type(x))
	{
		std::getline(in, dummy);
	}
	return in;
}

// Tests whether a string starts with a given prefix
bool polyfem::StringUtils::startswith(const std::string &str, const std::string &prefix) {
	return (str.compare(0, prefix.size(), prefix) == 0);
}

// Tests whether a string ends with a given suffix
bool polyfem::StringUtils::endswidth(const std::string &str, const std::string &suffix) {
	if (str.length() >= suffix.length()) {
		return (0 == str.compare(str.length() - suffix.length(), suffix.length(), suffix));
	} else {
		return false;
	}
}

// Replace extension after the last "dot"
std::string polyfem::StringUtils::replace_ext(const std::string &filename, const std::string &newext) {
	std::string ext = "";
	if (!newext.empty()) {
		ext = (newext[0] == '.' ? newext : "." + newext);
	}
	size_t lastdot = filename.find_last_of(".");
	if (lastdot == std::string::npos) {
		return filename + ext;
	}
	return filename.substr(0, lastdot) + ext;
}
