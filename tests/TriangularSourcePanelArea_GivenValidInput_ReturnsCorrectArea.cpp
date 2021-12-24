
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
	double correct_area = 0.5;

	if (panel.area() == correct_area)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

