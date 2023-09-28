#pragma once

#include <algorithm>
#include <map>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace utils {

enum {
	REMOVE_EMPTY = 0x01, /** REMOVE_EMPTY: remove empty elements. */
	STRIP_SPACES = 0x02  /** STRIP_SPACES: strips leading and trailing blank spaces. */
};


void trim(std::string_view& s)
{
	s.remove_prefix(std::min(s.find_first_not_of(" \t\r\n"), s.size()));
	if(s.empty()) {
		return;
	}
	//find_last_not_of never returns npos because !s.empty()
	size_t first_to_trim = s.find_last_not_of(" \t\r\n") + 1;
	s = s.substr(0, first_to_trim);
}

template<typename F>
void split_foreach_impl(std::string_view s, char sep, const F& f)
{
	if(s.empty()) {
		return;
	}
	while(true)
	{
		std::size_t partend = s.find(sep);
		if(partend == std::string_view::npos) {
			break;
		}
		f(s.substr(0, partend));
		s.remove_prefix(partend + 1);
	}
	f(s);
}

template<typename F>
void split_foreach(std::string_view s, char sep, const int flags, const F& f)
{
	split_foreach_impl(s, sep, [&](std::string_view item) {
		if(flags & STRIP_SPACES) {
			trim(item);
		}
		if(!(flags & REMOVE_EMPTY) || !item.empty()) {
			f(item);
		}
	});
}

/** Splits a (comma-)separated string into a vector of pieces. */
std::vector<std::string> split(std::string_view val, const char c = ',', const int flags = REMOVE_EMPTY | STRIP_SPACES);


} // end namespace utils