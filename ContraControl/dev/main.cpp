#include "Model/model_main.h"
#include "Controller/controller_main.h"


int main() {
	controller::initalize();
	model::initalize();

	controller::loop();
	model::loop();
	return 0;
}