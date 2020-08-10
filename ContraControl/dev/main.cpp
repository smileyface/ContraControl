#include "Model/model_main.h"
#include "Controller/controller_main.h"
#include "Utilities/utils.h"


int main() {
	file_reader::read_file();

	controller::initalize();
	model::initalize();
	while (1) {
		controller::loop();
		model::loop();
	}
	return 0;
}