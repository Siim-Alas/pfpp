
#include <iostream>

#include "binary_stl_parser.h"
#include "source_panel_method.h"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Invalid number of command line arguments\n";
		return 1;
	}

	lapp::vec<3, float> reaction_coefficient = { 0, 0, 0 };
	lapp::vec<3, float> u_infty = { 10, 0, 0 };

	std::cout << "Parsing STL...";

	auto [number_of_panels, source_panels] =
		pfpp::binary_stl_parser::parse_stl(argv[1]);

	if (number_of_panels == 0)
	{
		return 1;
	}

	std::cout << " done (a total of " << number_of_panels << " panels read)\n";
	std::cout << "Solving for the source strengths...";

	pfpp::source_panel_method::solve<float>(
			source_panels, u_infty, reaction_coefficient, number_of_panels);

	std::cout << " done\n";

	delete[] source_panels;

	std::cout << "Reaction coefficient = [" << reaction_coefficient.elements[0]
		<< "; " << reaction_coefficient.elements[1] << "; "
		<< reaction_coefficient.elements[2] << "]\n";

	return 0;
}

