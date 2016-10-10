#include <string>

class FileHandler{
	private:
		void file_opener();

	public:
		int* read_file(int * data);
		void write_to_file(std::string result);
};