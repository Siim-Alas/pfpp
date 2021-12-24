#pragma once

#include "../out/_deps/lapp-src/src/vec.h"

namespace pfpp
{
	template <typename T>
	struct triangular_source_panel
	{
		lapp::vec<3, T> N;
		lapp::vec<3, T> A;
		lapp::vec<3, T> B;
		lapp::vec<3, T> C;

		const lapp::vec<3, T> centroid() const
		{
			return (A + B + C) / 3;
		}
	};
}

