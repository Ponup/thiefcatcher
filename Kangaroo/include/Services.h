#pragma once

#include <vector>
using std::vector;

#include "Service.h"

namespace Kangaroo {

	class Services {

		vector<Service*> services;

	public:
		void addService(Service* service);
		void init();
		void destroy();
	};

}
