#pragma once

#define _USE_MATH_DEFINES

#include <cmath>	// std::sqrt

#include "../out/_deps/lapp-src/src/matops.h"
#include "../out/_deps/lapp-src/src/vec.h"

#include "triangular_source_panel.h"

namespace pfpp::source_panel_method
{
	/*
	 * Finds the required suource strengths of the triangular source panels such
	 * that the tangential flow constraint is satisfied for the given far field
	 * velocity. The triangular source panels are modeled as point sources
	 * located at their centroids.
	 *
	 * Parameters:
	 * 	- N, the number of triangular source panels;
	 * 	- T, the type of element in all of the vectors;
	 * 	- source_panels, a pointer to the start of the array containing the
	 * 	triangular source panels (it is assumed that no two panels have the same
	 * 	centroid);
	 * 	- u_infty, a vector giving the far field flow velocity (-1 times the
	 * 	body velocity);
	 * 	- results, a pointer to the start of the array to which the results are
	 * 	saved.
	 *
	 * Returns:
	 * 	void
	 */
	template <size_t N, typename T>
	void find_source_strengths(
		const pfpp::triangular_source_panel<T> source_panels[N],
		const lapp::vec<3, T> &u_infty,
		T results[N])
	{
		T equation_array[N][N + 1];

		for (int i = 0; i < N; i++)
		{
			lapp::vec<3, T> current_pos = source_panels[i].centroid();
			lapp::vec<3, T> n = source_panels[i].N;

			for (int j = 0; j < N; j++)
			{
				lapp::vec<3, T> dx = source_panels[j].centroid() - current_pos;
				T sqr_dist = dx.sqr_len();
				T dist = std::sqrt(sqr_dist);
				T S = source_panels[j].area();

				equation_array[i][j] =
					(dist == 0) ? 0 : n.dot(dx) * S / (dist * sqr_dist);
			}

			equation_array[i][N] = 4 * M_PI * n.dot(u_infty);
		}

		lapp::matops::solve_linear_system_in_place_with_gaussian_elimination<N, T>(equation_array, results);
	}
}

