#include "Library.h"

Library::Library(const std::string& file) {
	std::ifstream in(file);

	if (in.is_open()) {
		std::string name;
		int id, type;
		
		while (!in.eof()) {
			in >> id;
			if (id != -1) {
				in >> name >> type;

				if (type == Variant::TEXT) {
					std::string temp; in >> temp;
					mData.push_back(new Record(id, name, Variant(temp)));
				}
				else if (type == Variant::NUMBER) {
					double number; in >> number;
					mData.push_back(new Record(id, name, Variant(number)));
				}
				else if (type == Variant::COMPLEXNUM) {
					float re, im; in >> re >> im;
					mData.push_back(new Record(id, name, Variant(ComplexNum(re, im))));
				}
				else {
					//se poate dezvolta mai tare clasa de locatie dar asta este varianta conceptuala in care stringul contine adresa fara spatii dar cu virgule ca si separator de informatii
					std::string temp; in >> temp;
					mData.push_back(new Record(id, name, Variant(Location(temp))));
				}
			}
		}
	}
}

void Library::Save(const std::string& file) {
	std::ofstream out(file);

	for (unsigned int i = 0; i < mData.size(); ++i) {
		out << mData[i]->ID << " " << mData[i]->Name << " " << mData[i]->Data.Type() << " ";

		if (mData[i]->Data.Type() == Variant::TEXT) out << mData[i]->Data.GetString();
		else if (mData[i]->Data.Type() == Variant::NUMBER) out << mData[i]->Data.GetNumber();
		else if (mData[i]->Data.Type() == Variant::COMPLEXNUM) out << mData[i]->Data.GetComplexNum().mRe << " " << mData[i]->Data.GetComplexNum().mIm;
		else if (mData[i]->Data.Type() == Variant::LOCATION) out << mData[i]->Data.GetLocation().mLocation;

		out << "\n";
	}

	out << "-1";
}

int Library::GetLastID() {
	if (mData.size()) return mData.back()->ID;
	//default
	else return 0;
}

void Library::Add(const std::string& name, Variant value) {
	int id = -1, lastID = GetLastID();
	if(name != "-") FindByName(name);
	
	if (id == -1)
		mData.push_back(new Record(lastID + 1, name, value));
	else if (value.Type() == Variant::LOCATION) std::cout << "Eroare! Nu putem lipi doua locatii!";
	else
		mData[id]->Data = mData[id]->Data + value;
}

int Library::FindByID(int id) {
	for (unsigned int i = 0; i < mData.size(); ++i) if (mData[i]->ID == id) return i;
	return -1;
}

int Library::FindByName(const std::string& name) {
	for (unsigned int i = 0; i < mData.size(); ++i) if (mData[i]->Name == name) return i;
	return -1;
}

std::vector<int> Library::FindByValue(double value) {
	std::vector<int> ret;

	for (unsigned int i = 0; i < mData.size(); ++i) {
		if ((mData[i]->Data.Type() == Variant::NUMBER && mData[i]->Data.GetNumber() == value) || (mData[i]->Data.Type() == Variant::COMPLEXNUM && (mData[i]->Data.GetComplexNum().mIm == (float)value || mData[i]->Data.GetComplexNum().mRe == (float)value)))
			ret.push_back(i);
	}

	return ret;
}

std::vector<int> Library::FindByText(const std::string& val) {
	std::vector<int> ret;

	for (unsigned int i = 0; i < mData.size(); ++i) {
		if ((mData[i]->Data.Type() == Variant::TEXT && mData[i]->Data.GetString().find(val) != std::string::npos) || (mData[i]->Data.Type() == Variant::LOCATION && mData[i]->Data.GetLocation().mLocation.find(val) != std::string::npos))
			ret.push_back(i);
	}

	return ret;
}

void Library::Print(int id) {
	if (id >= mData.size()) return;

	std::cout << "Date gasite: " << mData[id]->Data;
}
