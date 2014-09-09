/*
	Raúl Negrón
	#801-13-4680

	frac.h

	This is the specifications for the Fraction class.

*/


#ifndef FRAC_H
#define FRAC_H

class Fraction {
	private:
		int num;
		int denom;
		
		double value;

	public:
		Fraction();
		Fraction(int, int);
		int getNum() const;
		int getDenom() const;
		void setNum(int);
		void setDenom(int);
		void print();

		double getValue();


		bool gt(const Fraction&);

		Fraction add(const Fraction& F) const;
		Fraction sub(const Fraction& F) const;
		Fraction mul(const Fraction& F) const;
		Fraction div(const Fraction& F) const;
		Fraction reduce();
};

#endif