#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "Variant.h"

struct Record {
	int ID;
	std::string Name;
	Variant Data;

	Record(int id, const std::string& name, Variant data) {
		ID = id;
		Name = name;
		Data = data;
	}
};

class Library {
	public:
		Library(const std::string& file);
		~Library();

		void Save(const std::string& file);

		void Add(const std::string& name, Variant value);
		void Add(Variant value) { Add("-", value); }

		void Delete(int id) { if (id >= mData.size()) return; mData.erase(mData.begin() + id); }

		int FindByID(int id);
		int FindByName(const std::string& name);

		std::vector<int> FindByValue(double val);
		std::vector<int> FindByText(const std::string& val);

		void Print(int id);
		Record* Get(int id) { if (id >= mData.size()) return NULL; return mData[id]; }

	private:
		std::vector<Record*> mData;

		int GetLastID();


};

#endif
