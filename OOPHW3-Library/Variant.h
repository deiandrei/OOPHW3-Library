#ifndef VARIANT_H
#define VARIANT_H

#include <string>

#include "ComplexNum.h"
#include "Location.h"

class Variant {
	public:
		enum INTERN_TYPE { TEXT, NUMBER, COMPLEXNUM, LOCATION };

	public:
		Variant() { }
		Variant(const std::string& data) { String = data; mType = TEXT; }
		Variant(double data) { Number = data; mType = NUMBER; }
		Variant(ComplexNum data) { Complex = data; mType = COMPLEXNUM; }
		Variant(Location data) { Loc = data; mType = LOCATION; }

		INTERN_TYPE Type() { return mType; }
		std::string& GetString() { return String; }
		double& GetNumber() { return Number; }
		ComplexNum& GetComplexNum() { return Complex; }
		Location& GetLocation() { return Loc; }

		/*
		Variant& operator=(Variant& obj) {
			mType = obj.mType;

			if (mType == TEXT) String = obj.String;
			else if (mType == NUMBER) Number = obj.Number;
			else if (mType == COMPLEXNUM) Complex = obj.Complex;

		}
		*/

		Variant operator+(Variant& obj) {
			if (obj.mType != mType) return Variant(0.0);

			Variant temp;
			temp.mType = mType;
			if (mType == TEXT) { temp.String = String + obj.String; }
			else if (mType == NUMBER) { temp.Number = Number + obj.Number; }
			else if (mType == COMPLEXNUM) { temp.Complex = Complex + obj.Complex; }
			else temp = *this;

			return temp;
		}

		friend std::ostream& operator<<(std::ostream& os, const Variant& obj) {
			if (obj.mType == TEXT) os << obj.String;
			else if (obj.mType == NUMBER) os << obj.Number;
			else if (obj.mType == COMPLEXNUM) os << obj.Complex;
			else os << obj.Loc;

			return os;
		}

	private:
		INTERN_TYPE mType;
		
		//am incercat cu union dar mai rau am facut
		std::string String;
		double Number;
		ComplexNum Complex;
		Location Loc;

};

#endif
