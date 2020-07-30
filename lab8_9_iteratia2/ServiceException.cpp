#include "ServiceException.h"


ostream& operator<<(ostream& out, const ServiceException& ex) {
	out << ex.msg;
	return out;
}