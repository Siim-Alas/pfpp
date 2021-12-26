
#include <chrono>

#include "binary_stl_parser.h"
#include "source_panel_method.h"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Invalid number of command line arguments\n");
		return 1;
	}

	lapp::vec<3, float> reaction_coefficient = { 0, 0, 0 };
	lapp::vec<3, float> u_infty = { 10, 0, 0 };

	printf("Parsing STL...");

	auto [number_of_panels, source_panels] =
		pfpp::binary_stl_parser::parse_stl(argv[1]);

	if (number_of_panels == 0)
	{
		return 1;
	}

	printf(" done (a total of %d panels read)\n", number_of_panels);
	printf("Solving...");

	std::chrono::high_resolution_clock::time_point t1 =
		std::chrono::high_resolution_clock::now();

	pfpp::source_panel_method::solve<float>(
			source_panels, u_infty, reaction_coefficient, number_of_panels);

	std::chrono::high_resolution_clock::time_point t2 =
		std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span =
		std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

	printf(" done (solved in %f seconds)\n", time_span.count());

	delete[] source_panels;

	printf("Reaction coefficient = [%f; %f; %f]\n",
		reaction_coefficient.elements[0],
		reaction_coefficient.elements[1],
		reaction_coefficient.elements[2]);

	return 0;
}

