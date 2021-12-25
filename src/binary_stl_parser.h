
#include <cstdio>
#include <utility>

#include "triangular_source_panel.h"

namespace pfpp::binary_stl_parser
{
	std::pair<size_t, pfpp::triangular_source_panel<float>*>
	parse_stl(const char *filename);
}

