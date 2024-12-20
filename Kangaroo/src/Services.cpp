#include "Services.h"

using namespace Kangaroo;

void Services::addService(Service* service) {
	services.push_back(service);
}

void Services::init() {
	for (unsigned int i = 0; i < services.size(); i++) {
		Service *service = services.at(i);
		service->init();
	}
}

void Services::destroy() {
	for (unsigned int i = services.size() - 1; i > 0; i--) {
		Service *service = dynamic_cast<Service *>(services.at(i));
		service->destroy();
	}
	services.clear();
}

