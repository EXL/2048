#include "2048.h"

//#include <bool.h>

class Application {
public:
	Application(void) {
		e_init(kEscapeCharCode, kLeftArrowCharCode, kRightArrowCharCode, kUpArrowCharCode, kDownArrowCharCode);
	}
	~Application(void) {
		
	}
	
	bool CheckColorMac(void) {
		return true;
	}
	
	void InitMac(void) {
		
	}
	
	void Run(void) {
	
	}
};

int main(void) {
	Application *app = new Application();
	if (app->CheckColorMac()) {
		app->InitMac();
		app->Run();
	}
	delete app;
	return 0;
}
