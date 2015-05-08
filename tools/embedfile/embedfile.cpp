/**
 * Originally written by z64555
 * Adapted to use stdlib by m!m
 */

// ToDo: Review wxWidgets API to file input and output
// Correct the code so that the program will properly output text to a target .h file
// Correct the code so that the program will properly read bytes in and output as hexidecimal string values.

#include <string.h>

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

bool casecmp(const char* strA, const char* strB)
{
	size_t lenA = strlen(strA);

	if (lenA != strlen(strB))
	{
		return false;
	}

	for (size_t i = 0; i < lenA; i++)
	{
		if (toupper(strA[i]) != toupper(strB[i]))
			return false;
	}

	return true;
}

// Input: Filename of file to convert
// Function output: standard status codes
// Side-effect output: converted file
enum embedpng_errors
{
	error_none = 0,
	error_cantopenfile,
	error_cantoutputfile,
	error_invalidargs,
	error_ioerror,
};

static const size_t INPUT_BUFFER_SIZE = 1024;

typedef unsigned char ubyte;

void write_byte(std::ostream& stream, ubyte byte, int i)
{
	stream << "0x" << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << int(byte);

	if( (i % 16) == 0 )
	{
		// End of 16-byte row
		stream << "," << std::endl;
		stream << "\t";
	}
	else
	{
		// Somewhere within a column
		stream << ", ";
	}
}

void do_binary_content(std::ifstream& file_in, std::ofstream& file_out,
					   const std::string& field_name, size_t input_size, bool wxWidgets_image)
{
	if (wxWidgets_image)
	{
		file_out << "#include <wx/mstream.h>" << std::endl;
		file_out << "#include <wx/image.h>" << std::endl;
		file_out << "#include <wx/bitmap.h>" << std::endl;
		file_out << std::endl;
	}

	file_out << "static const unsigned char " << field_name << "[] = " << std::endl;
	file_out << "{" << std::endl;
	file_out << "\t";

	ubyte buffer[INPUT_BUFFER_SIZE];

	size_t i = 0;
	while(i < input_size)
	{
		size_t current_size = std::min(input_size - i, INPUT_BUFFER_SIZE);
		file_in.read((char*) buffer, current_size);

		for (size_t j = 0; j < current_size; j++)
		{
			i++;
			write_byte(file_out, buffer[j], i);
		}
	}

	file_out << std::endl;

	file_out << "};" << std::endl;

	if (wxWidgets_image)
	{
		file_out << std::endl;

		file_out << "wxBitmap& " << field_name << "_to_wx_bitmap()" << std::endl;
		file_out << "{" << std::endl;
		file_out << "\tstatic wxMemoryInputStream memIStream( " << field_name << ", sizeof( " << field_name << " ) );" << std::endl;
		file_out << "\tstatic wxImage image( memIStream );" << std::endl;
		file_out << "\tstatic wxBitmap bmp( image );" << std::endl;
		file_out << "\treturn bmp;" << std::endl;
		file_out << "};" << std::endl;
	}
}

void do_text_content(std::ifstream& file_in, std::ofstream& file_out,
					   const std::string& field_name, size_t input_size)
{
	const char* escapeCharacters = "\\\"\n\r";

	std::string file_content;
	file_content.reserve(input_size);

	file_content.assign((std::istreambuf_iterator<char>(file_in)),
				std::istreambuf_iterator<char>());

	file_out << "char *" << field_name << " = " << std::endl;
	file_out << "\"";

	size_t pos = 0;
	const char* str = file_content.c_str();

	while (pos < file_content.length())
	{
		const char* found_ptr = strpbrk(str + pos, escapeCharacters);

		if (!found_ptr)
		{
			file_out.write(str + pos, file_content.length() - pos);
			break;
		}
		else
		{
			size_t found_pos = (size_t) (found_ptr - str);

			size_t delta = found_pos - pos;

			if (delta != 0)
			{
				file_out.write(str + pos, delta);
			}

			switch(str[found_pos])
			{
			case '\\':
				file_out << "\\\\";
				break;
			case '\n':
				file_out << "\\n\"" << std::endl << "\"";
				break;
			case '"':
				file_out << "\\\"";
				break;
			case '\r':
				// Discard this character, possibly breaks on mac but whatever...
				break;
			default:
				std::cout << "ERROR: Invalid character encountered!" << std::endl;
			}

			pos = found_pos + 1;
		}
	}

	file_out << "\";" << std::endl;
}

int main( int argc, char* argv[] )
{
	if (argc < 4 || argc > 6)
	{
		std::cout << "Usage: embedfile [-wx] [-text] <inout> <output> <fieldname>" << std::endl;

		return error_invalidargs;
	}

	bool wxWidgets_image = false;
	bool text_content = false;

	int argc_offset = 1;

	if (casecmp(argv[argc_offset], "-wx"))
	{
		wxWidgets_image = true;

		argc_offset++;
	}

	if (casecmp(argv[argc_offset], "-text"))
	{
		text_content = true;

		argc_offset++;
	}

	std::string input_file(argv[argc_offset]);
	std::string output_file(argv[argc_offset + 1]);
	std::string field_name(argv[argc_offset + 2]);

	std::ios::openmode mode = std::ios::in;
	if (!text_content)
	{
		mode |= std::ios::binary;
	}

	std::ifstream file_in(input_file.c_str(), std::ios::binary);
	if( file_in.bad() )
	{
		std::cout << "ERROR: Error opening input file: " << input_file << std::endl;
		return error_cantopenfile;
	}

	// Get the size of the input stream
	size_t input_size;
	file_in.seekg(0, std::ios::end);

	if ((int) file_in.tellg() != -1)
	{
		input_size = (size_t) file_in.tellg();
	}
	else
	{
		std::cout << "ERROR: Failed to get size of input file: " << input_file << std::endl;
		file_in.close();
		return error_ioerror;
	}

	file_in.seekg(0, std::ios::beg);

	// Before conditioning, use this a the name of the .h
	std::ofstream file_out(output_file.c_str());
	if(file_out.bad())
	{
		std::cout << "ERROR: Error opening output file: " << output_file << std::endl;
		file_in.close();
		return error_cantoutputfile;
	}

	if (text_content)
	{
		do_text_content(file_in, file_out, field_name, input_size);
	}
	else
	{
		do_binary_content(file_in, file_out, field_name, input_size, wxWidgets_image);
	}

	file_in.close();
	file_out.close();

	return error_none;
}
