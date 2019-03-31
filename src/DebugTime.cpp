#include "DebugTime.h"
#include "DebugInfo.h"

#ifndef NDEBUGTIME
std::ostream &DebugTime::printPressHistory(std::ostream &os) {
	os << "Press Time: \t";
	for (double t : v) os << t << '\t';
	os << "\nPress Interval: \t" << v[0] << '\t';
	for (auto it = v.cbegin(); it != v.cend() - 1; ++it) {
		os << it[1] - it[0] << '\t';
	}
	return os;
}

std::ostream &DebugTime::printTime(const std::string &s, std::ostream &os, double exclude) {
	os << s << " Time: " << getSeconds() - exclude << " s" << std::endl;
	return os;
}
std::ostream &DebugTime::printTimeAndRestart(const std::string &s, std::ostream &os, double exclude) {
	os << s << " Time: " << getSeconds() - exclude << " s" << std::endl;
	restart();
	return os;
}
#endif