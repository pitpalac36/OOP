#include "RepoException.h"


ostream& operator<<(ostream& out, const RepoException& ex) {
	out << ex.msg;
	return out;
}