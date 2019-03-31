#ifndef DEBUG_TIME_H
#define DEBUG_TIME_H

#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include "DebugInfo.h"

#ifndef NDEBUGTIME
class DebugTime {	// a watch
private:
	clock_t b = 0;
	clock_t e = 0;
	bool p = false;
	double limit = 0;
	std::vector<double> v;

public:
	DebugTime() : b(clock()) {}
	explicit DebugTime(double timeLimit) : b(clock()), limit(timeLimit) {}
	void restart() { p = false; b = clock(); v = {}; }
	void restartAndPause() { b = e = clock(); p = true; v = {}; }
	void setTimeLimit(double timeLimit) { limit = timeLimit; }
	clock_t getClocks() { return (p ? e : clock()) - b; }
	double getSeconds() { return static_cast<double>(getClocks()) / CLOCKS_PER_SEC; }
	bool isTimeout() { return getSeconds() > limit; }
	bool isTimeout(double limit) { return getSeconds() > limit; }
	void press() { v.push_back(getSeconds()); }
	void pause() { if (!p) { p = true; e = clock(); } }
	void continueAfterPause() { if (p) { p = false; b += clock() - e; } }
	std::vector<double> &getPressTimeVector() { return v; }
	std::ostream &printPressHistory(std::ostream &os = std::cout);
	std::ostream &printTime(const std::string &s = "", std::ostream &os = std::cout, double exclude = 0);
	std::ostream &printTimeAndRestart(const std::string &s = "", std::ostream &os = std::cout, double exclude = 0);
};
#else
struct DebugTime {
	std::vector<double> v;
	DebugTime() {}
	explicit DebugTime(double) {}
	void restart() {}
	void restartAndPause() {}
	void pause() {}
	void continueAfterPause() {}
	void setTimeLimit(double) {}
	clock_t getClocks() { return 0; }
	double getSeconds() { return 0; }
	bool isTimeout() { return false; }
	bool isTimeout(double) { return false; }
	void press() {}
	std::vector<double> &getPressTimeVector() { return v; }
	std::ostream &printPressHistory(std::ostream &os = std::cout) { return os; }
	std::ostream &printTime(const std::string &s = "", std::ostream &os = std::cout, double exclude = 0) { return os; }
	std::ostream &printTimeAndRestart(const std::string &s = "", std::ostream &os = std::cout, double exclude = 0) { return os; }
};
#endif	// NDEBUGTIME

#endif // DEBUG_TIME_H