#include "string_utils.hpp"


namespace utils {

std::vector<std::string> split(std::string_view s, const char sep, const int flags)
{
	std::vector<std::string> res;
	split_foreach(s, sep, flags, [&](std::string_view item) {
		res.emplace_back(item);
	});
	return res;
}


} // end namespace utils