#pragma once

#include <cmath>	// std::sqrt

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

		const T area() const
		{
			lapp::vec<3, T> AB = B - A;
			lapp::vec<3, T> AC = C - A;
			T AB_dot_AC = AB.dot(AC);

			return 0.5 * std::sqrt(
				AB.sqr_len() * AC.sqr_len() - AB_dot_AC * AB_dot_AC);
		}

		const lapp::vec<3, T> centroid() const
		{
			return (A + B + C) / 3;
		}
	};
}

