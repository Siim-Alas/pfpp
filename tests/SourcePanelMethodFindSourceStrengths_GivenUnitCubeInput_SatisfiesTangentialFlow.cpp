
#include <cmath>
#include <iostream>

#include "../src/source_panel_method.h"

int main()
{
	const size_t N = 12; // A cube has 6 faces, each consisting of two triangles
	const float allowable_error = 1e-4;
	pfpp::triangular_source_panel<float> source_panels[N] =
	{
		{
			{   1,    0,    0 },
			{ 0.5,  0.5, -0.5 },
			{ 0.5,  0.5,  0.5 },
			{ 0.5, -0.5,  0.5 },
			{  -1,   -1,   -1 },
			-1
		},
		{
			{   1,    0,    0 },
			{ 0.5,  0.5, -0.5 },
			{ 0.5, -0.5, -0.5 },
			{ 0.5, -0.5,  0.5 },
			{  -1,   -1,   -1 },
			-1
		},
		{
			{   -1,    0,    0 },
			{ -0.5,  0.5, -0.5 },
			{ -0.5,  0.5,  0.5 },
			{ -0.5, -0.5,  0.5 },
			{   -1,   -1,   -1 },
			-1
		},
		{
			{   -1,    0,    0 },
			{ -0.5,  0.5, -0.5 },
			{ -0.5, -0.5, -0.5 },
			{ -0.5, -0.5,  0.5 },
			{   -1,   -1,   -1 },
			-1
		},
		{
			{    0,   1,    0 },
			{  0.5, 0.5, -0.5 },
			{ -0.5, 0.5, -0.5 },
			{ -0.5, 0.5,  0.5 },
			{  -1,   -1,   -1 },
			-1
		},
		{
			{    0,   1,    0 },
			{  0.5, 0.5, -0.5 },
			{  0.5, 0.5,  0.5 },
			{ -0.5, 0.5,  0.5 },
			{  -1,   -1,   -1 },
			-1
		},
		{
			{    0,   -1,    0 },
			{  0.5, -0.5, -0.5 },
			{ -0.5, -0.5, -0.5 },
			{ -0.5, -0.5,  0.5 },
			{   -1,   -1,   -1 },
			-1
		},
		{
			{    0,   -1,    0 },
			{  0.5, -0.5, -0.5 },
			{  0.5, -0.5,  0.5 },
			{ -0.5, -0.5,  0.5 },
			{   -1,   -1,   -1 },
			-1
		},
		{
			{    0,    0,   1 },
			{  0.5,  0.5, 0.5 },
			{ -0.5,  0.5, 0.5 },
			{  0.5, -0.5, 0.5 },
			{   -1,   -1,  -1 },
			-1
		},
		{
			{    0,    0,   1 },
			{ -0.5,  0.5, 0.5 },
			{ -0.5, -0.5, 0.5 },
			{  0.5, -0.5, 0.5 },
			{   -1,   -1,  -1 },
			-1
		},
		{
			{    0,    0,   -1 },
			{  0.5,  0.5, -0.5 },
			{ -0.5,  0.5, -0.5 },
			{  0.5, -0.5, -0.5 },
			{   -1,   -1,   -1 },
			-1
		},
		{
			{    0,    0,   -1 },
			{ -0.5,  0.5, -0.5 },
			{ -0.5, -0.5, -0.5 },
			{  0.5, -0.5, -0.5 },
			{   -1,   -1,   -1 },
			-1
		},
	};

	for (int i = 0; i < N; i++)
	{
		source_panels[i].compute_centroid();
		source_panels[i].compute_surface_area();
	}

	lapp::vec<3, float> u_infty = { 10, 0, 0 };
	float results[N];

	pfpp::source_panel_method::find_source_strengths<float>(source_panels, u_infty, results, N);

	for (int i = 0; i < N; i++)
	{
		lapp::vec<3, float> current_pos = source_panels[i].centroid;
		lapp::vec<3, float> sum = u_infty;

		for (int j = 0; j < N; j++)
		{
			lapp::vec<3, float> dx = current_pos - source_panels[j].centroid;
			float sqr_dist = dx.sqr_len();

			if (sqr_dist == 0)
			{
				continue;
			}

			sum += (float)(results[j] / (4 * M_PI * sqr_dist * std::sqrt(sqr_dist))) *
				source_panels[j].surface_area * dx;
		}

		if (std::abs(sum.dot(source_panels[i].N)) > allowable_error)
		{
			return 1;
		}
	}

	return 0;
}

