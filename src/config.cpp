/**
 * @author Graeme Prendergast
 */

#include <algorithm>
#include <iterator>

#include "config.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


std::vector<std::string> split(std::string const& str, std::string const& delimiter)
{
	if (str.empty())
		return { };

	std::vector<std::string> tokens;

	size_t token_begin = 0, token_end = 0;
	while ((token_end = str.find(delimiter, token_begin)) != std::string::npos)
	{
		if (token_end - token_begin < 2)  // multiple adjacent delimiters encountered
		{
			token_begin = token_end + 1;
			continue;
		}

		std::string const token = str.substr(token_begin, token_end - token_begin);
		tokens.push_back(token);
		token_begin = token_end + 1;
	}

	std::string const last_token = str.substr(token_begin, token_end - token_begin);
	tokens.push_back(last_token);

	return tokens;
}

std::string to_string(std::vector<std::string> const& vec)
{
	if (vec.empty())
	{
		return "{ }";
	}

	std::stringstream buffer;

	buffer << "{ \"";
	std::copy(vec.begin(), vec.end()-1, 
		std::ostream_iterator<std::string>(buffer, "\", \"")
	);
	buffer << vec.back() << "\" }";

	return buffer.str();
}
