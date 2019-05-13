#ifndef UTILS_H
#define UTILS_H

#include "User.h"

namespace Utils {

	void LoadDB(const std::string& filename, std::vector<User*>& vec) {
		std::ifstream in(filename);

		if (in.is_open()) {
			while (!in.eof()) {
				std::string user, pass; in >> user >> pass;
				vec.push_back(new User(user, pass));
			}
		}
	}

};

#endif
