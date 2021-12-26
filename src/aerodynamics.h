#pragma once

#define _USE_MATH_DEFINES

#include <cmath>	// std::sqrt

#include "../out/_deps/lapp-src/src/matops.h"
#include "../out/_deps/lapp-src/src/vec.h"

#include "triangular_source_panel.h"

namespace pfpp::aerodynamics
{
	template <typename T>
	const lapp::vec<3, T> reaction_coefficient(
		const triangular_source_panel<T> *source_panels,
		const T *source_strengths,
		const lapp::vec<3, T> &u_infty,
		size_t number_of_panels)
	{
		T total_area = 0;

		lapp::vec<3, T> reaction_coefficient = { 0, 0, 0 };
		T sqr_len_of_u_infty = u_infty.sqr_len();

		for (int i = 0; i < number_of_panels; i++)
		{
			lapp::vec<3, T> current_pos = source_panels[i].centroid;
			lapp::vec<3, T> u = u_infty;

			for (int j = 0; j < number_of_panels; j++)
			{
				lapp::vec<3, T> dx = current_pos - source_panels[j].centroid;
				T sqr_dist = dx.sqr_len();

				if (sqr_dist == 0)
				{
					continue;
				}

				u += (T)(source_strengths[j] / (sqr_dist * std::sqrt(sqr_dist)))
					* dx;
			}

			u /= (T)(4 * M_PI);

			// For an outward-pointing unit normal vector source_panels[i].N
			reaction_coefficient -= (1 - u.sqr_len() / sqr_len_of_u_infty) *
				source_panels[i].surface_area * source_panels[i].N;

			total_area += source_panels[i].surface_area;
		}

		reaction_coefficient /= total_area;

		return reaction_coefficient;
	}
}

