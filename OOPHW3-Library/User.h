#ifndef USER_H
#define USER_H

#include <vector>
#include <string>
#include <fstream>

class User {
	public:
		User(const std::string& name, const std::string& pass) : mName(name), mPass(pass) { }

		std::string GetName() { return mName; }
		std::string GetPass() { return mPass; }

	private:
		std::string mName, mPass;

};

#endif
