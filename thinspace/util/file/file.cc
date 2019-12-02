
#include "file.h"

namespace util {
namespace file {

std::string Load(const std::string& file_path) {

	std::string buffer;
	std::ifstream stream(file_path);

	if(stream.is_open()) {

		std::string line;

		while(!stream.eof()) {

			std::getline(stream, line);
			buffer += line + "\n";
			
		}

		stream.close();
	}

	return buffer;
}

} // namespace file
} // namespace util