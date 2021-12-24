
#include "../src/triangular_source_panel.h"

int main()
{
	pfpp::triangular_source_panel<double> panel =
	{
		{ 1, 0, 0},
		{ 0, 0, 0},
		{ 0, 1, 0},
		{ 0, 0, 1}
	};
	lapp::vec<3, double> correct_centroid = { 0, 1.0 / 3.0, 1.0 / 3.0 };

	if (panel.centroid() == correct_centroid)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

