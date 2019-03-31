#include <iostream>
#include "core.h"

using namespace std;

int main() {
	vector<vector<string>> res;
 	gen_chain_char_n({ "abc", "cde", "efg", "ghi","gui", "iba" }, 6, res);
	for (auto &v : res) {
		for (auto &s : v) {
			cout << s << ' ';
		}
		cout << endl;
	}
}