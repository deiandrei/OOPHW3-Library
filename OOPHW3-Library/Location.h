#pragma once

#include <string>

class Location {
	public:
		Location(const std::string& location) : mLocation(location) { }
		Location() { mLocation = ""; }

		std::string mLocation;

		friend std::ostream& operator<<(std::ostream& os, const Location& obj) {
			os << obj.mLocation;

			return os;
		}
};
