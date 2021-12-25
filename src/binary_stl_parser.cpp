
#include <cstdint>	// uint32_t
#include <iostream>	// std::cout

#include "binary_stl_parser.h"

std::pair<size_t, pfpp::triangular_source_panel<float>*>
pfpp::binary_stl_parser::parse_stl(const char *filename)
{
	const std::pair<size_t, triangular_source_panel<float>*> err_result(
		0, NULL);

	uint32_t num_of_panels;
	triangular_source_panel<float> *source_panels;

	FILE *stl_file = fopen(filename, "rb");
	if (stl_file == NULL)
	{
		std::cout << "Error opening the file '" << filename << "'\n";
		return err_result;
	}

	// Skip the 80-byte header
	if (fseek(stl_file, 80, SEEK_SET))
	{
		std::cout << "Error skipping the 80-byte header\n";
		return err_result;
	}

	// Assumes uint32_t is little-endian
	if (fread(&num_of_panels, sizeof(uint32_t), 1, stl_file) != 1)
	{
		std::cout << "Error reading the number of panels\n";
		return err_result;
	}

	source_panels = new triangular_source_panel<float>[num_of_panels];
	for (int i = 0; i < num_of_panels; i++)
	{
		// Read one triangle from the STL file
		if (fread(&(source_panels[i]), sizeof(triangular_source_panel<float>),
				1, stl_file) != 1)
		{
			std::cout << "Error reading the " << i << "-th source panel\n";
			return err_result;
		}

		// Skip the 2-byte "attribute byte count"
		if (fseek(stl_file, 2, SEEK_CUR))
		{
			std::cout << "Error skipping 2 bytes after the " << i
				<< "-th source panel\n";
			return err_result;
		}
	}

	if (fclose(stl_file))
	{
		std::cout << "Error closing the file\n";
		return err_result;
	}

	std::pair<size_t, triangular_source_panel<float>*> result(
		num_of_panels, source_panels);
	return result;
}

