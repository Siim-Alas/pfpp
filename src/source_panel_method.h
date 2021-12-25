#pragma once

#define _USE_MATH_DEFINES

#include <cmath>	// std::sqrt

#include "../out/_deps/lapp-src/src/mat.h"
#include "../out/_deps/lapp-src/src/vec.h"

#include "aerodynamics.h"
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
	 * 	- T, the type of element in all of the vectors;
	 * 	- source_panels, a pointer to the start of the array containing the
	 * 	triangular source panels (it is assumed that no two panels have the same
	 * 	centroid);
	 * 	- u_infty, a vector giving the far field flow velocity (-1 times the
	 * 	body velocity);
	 * 	- results, a pointer to the start of the array to which the results are
	 * 	saved;
	 * 	- num_of_panels, the number of triangular source panels.
	 *
	 * Returns:
	 * 	void
	 */
	template <typename T>
	void find_source_strengths(
		const pfpp::triangular_source_panel<T> *source_panels,
		const lapp::vec<3, T> &u_infty,
		T *results,
		size_t num_of_panels)
	{
		lapp::mat<T> equation_matrix(num_of_panels, num_of_panels + 1);

		for (int i = 0; i < num_of_panels; i++)
		{
			lapp::vec<3, T> current_pos = source_panels[i].centroid();
			lapp::vec<3, T> n = source_panels[i].N;

			for (int j = 0; j < num_of_panels; j++)
			{
				lapp::vec<3, T> dx = source_panels[j].centroid() - current_pos;
				T sqr_dist = dx.sqr_len();
				T dist = std::sqrt(sqr_dist);
				T S = source_panels[j].area();

				equation_matrix[i][j] =
					(dist == 0) ? 0 : n.dot(dx) * S / (dist * sqr_dist);
			}

			equation_matrix[i][num_of_panels] = 4 * M_PI * n.dot(u_infty);
		}

		equation_matrix.solve_linear_system_in_place(results);
	}

	template <typename T>
	void solve(
		const pfpp::triangular_source_panel<T> *source_panels,
		const lapp::vec<3, T> &u_infty,
		lapp::vec<3, T> &reaction_coefficient,
		size_t number_of_panels)
	{
		T *source_strengths = new T[number_of_panels];
		find_source_strengths<T>(
			source_panels, u_infty, source_strengths, number_of_panels);

		reaction_coefficient = aerodynamics::reaction_coefficient(
			source_panels, source_strengths, u_infty, number_of_panels);
	}
}

