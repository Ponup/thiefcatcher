#include "Services.h"

using namespace Kangaroo;

void Services::addService(Service* service) {
	services.push_back(service);
}

void Services::init() {
	for (const auto service : services) {
			service->init();
	}
}

void Services::destroy() {
	for (unsigned int i = services.size() - 1; i > 0; i--) {
		Service *service = services.at(i);
		service->destroy();
	}
	services.clear();
}

