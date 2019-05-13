#pragma once

#include <fstream>

class ComplexNum {
	public:
		ComplexNum(float re, float im) : mRe(re), mIm(im) { }
		ComplexNum() : mRe(0.0f), mIm(0.0f) { }

		ComplexNum operator+(ComplexNum& obj) {
			ComplexNum temp;
			temp.mRe = mRe + obj.mRe;
			temp.mIm = mIm + obj.mIm;
			return temp;
		}

		float mRe, mIm;

		friend std::ostream& operator<<(std::ostream& os, const ComplexNum& obj) {
			os << obj.mRe << " " << obj.mIm;

			return os;
		}

};
