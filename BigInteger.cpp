//-----------------------------------------------------------------------------
// Name: Lia Cui
// CRUZID: ljcui
// Assignment Name: PA6
//
//-----------------------------------------------------------------------------

#include<string>
#include<iostream>
#include<stdexcept>
#include<cmath>
#include<cstring>
#include "BigInteger.h"

//const long BASE = 1000000000;
const long BASE = 10;
const int POWER = 9;

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
    signum = 0;
    digits = List();

}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x){
    if(x > 0){
        this->signum = 1;
    }else if(x < 0){
        this->signum = -1;
    }else{
        this->signum = 0;
        return;
    }

    if (x < BASE) {
		digits.insertAfter(x);
	}
	else {
		long carry = x / BASE;
		long n = x - BASE * carry;
		digits.insertAfter(n);
		while (carry > 0) {
			x = carry / BASE;
			n = carry - x * BASE;
			digits.moveFront();
			digits.insertBefore(n);
			carry = x;
		}
	}

}


// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
    int length = (int)s.length();
    signum = 0;
    if(s.length() == 0){
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }else if(s.length() == 1){
        if(s[0] == '0'){
            return;
        }else if((s[0] < '0') || (s[0] > '9')){
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }else{
            signum = 1;
            digits.insertAfter(s[0] - '0');
        }

    }else{
        signum = 1;
        int start = 0;
        if(s[0] == '+'){
            signum = 1;
            start = 1;
        }else if(s[0] == '-'){
            signum = -1;
            start = 1;
        }

        while(s[start] == '0'){
            start++;
        }

        for(int i = start; i < length; i++){
            if((s[i] < '0') || (s[i] > '9')){
                throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
            }else{
                digits.insertBefore(s[i] - '0');
            }
        }


    }

    

}



// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
    this->signum = N.signum;
    this->digits = N.digits;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
    BigInteger diff = this->sub(N);
    return diff.sign();
}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
    this->signum = 0;
    this->digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
    if(this->digits.length() != 0){
        this->signum *= -1;
    }
}


// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger propA(*this);
    BigInteger propB(N);
    BigInteger sum;
    List digitSum;
    if(propA.sign() != propB.sign()){
        if(propB.sign() < 0){
            propB.signum *= -1;
            if(propA == propB){
                sum.signum = 0;
                return sum;
            }else if(propA > propB){
                int o = propA.digits.length() - propB.digits.length();
                propB.digits.moveFront();
                for(int i = 0; i < o; i++){
                    propB.digits.insertBefore(0);
                }
                sum.signum = 1;
                propA.digits.moveBack();
                propB.digits.moveBack();
                long carry = 0;
                while(propA.digits.position() > 0){
                    long a = propA.digits.peekPrev();
                    long b = propB.digits.peekPrev();
                    long plus = (a - b) + carry;
                    if(plus < 0){
                        plus = (a + BASE) - b + carry;
                        carry = -1;
                    }else{
                        carry = 0;
                    }

                    digitSum.insertAfter(plus);
                    propA.digits.movePrev();
                    propB.digits.movePrev();              
                }
                sum.digits = digitSum;

                sum.digits.moveFront();  // Clear leading zeros.
                while( sum.digits.position() < sum.digits.length() - 1) {
                    ListElement l = sum.digits.peekNext();
                    if (l == (ListElement) 0 ) {
                        sum.digits.eraseAfter();
                    } else {
                        break;
                    }
                }

                return sum;
            }else if(propA < propB){
                propA.signum *= -1;
                sum = propB.add(propA);
                sum.signum = -1;
                return sum;
            }else{
                sum.signum = 0;
                return sum;
            }
        }else if(propB.sign() > 0){
            return propB.add(propA);
        }else{
            return propA;
        }
    }else{
        sum.signum = signum;
        List digitsA = propA.digits;
        List digitsB = propB.digits;
        digitsA.moveBack();
        digitsB.moveBack();
        long carry = 0;
        while(digitsA.position() > 0 && digitsB.position() > 0){
            long a = digitsA.peekPrev();
            long b = digitsB.peekPrev();
            long plus = a + b + carry;
            carry = 0;
            while(plus >= BASE){
                plus -= BASE;
                carry += 1;
            }
            digitSum.insertAfter(plus);
            digitsA.movePrev();
            digitsB.movePrev();
            
        }

        while(digitsA.position() > 0){
            long a;
            if(carry > 0){
                a = digitsA.peekPrev() + carry;
            }else{
                a = digitsA.peekPrev();
            }

            carry = 0;

            while(a >= BASE){
                a -= BASE;
                carry += 1;
            }
            
            digitSum.insertAfter(a);
            digitsA.movePrev();
        }
        while(digitsB.position() > 0){
            long b;
            if(carry > 0){
                b = digitsB.peekPrev() + carry;
            }else{
                b = digitsB.peekPrev();
            }

            carry = 0;

            while(b >= BASE){
                b -= BASE;
                carry += 1;
            }

            digitSum.insertAfter(b);
            digitsB.movePrev();
        }
        if (carry > 0) {
            digitSum.insertAfter(carry);
        }

        sum.digits = digitSum;

        sum.digits.moveFront();  // Clear leading zeros.
        while( sum.digits.position() < sum.digits.length() - 1) {
            ListElement l = sum.digits.peekNext();
            if (l == (ListElement) 0 ) {
                sum.digits.eraseAfter();
            } else {
                break;
            }
        }

        return sum;

    }

    
    
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger propA = (*this);
	BigInteger propB = N;
    BigInteger diff;
	propB.negate();

	diff = propA.add(propB);

    diff.digits.moveFront();  // Clear leading zeros.
	while( diff.digits.position() < diff.digits.length() - 1) {
        ListElement l = diff.digits.peekNext();
        if (l == (ListElement) 0 ) {
            diff.digits.eraseAfter();
        } else {
            break;
        }
	}

    return diff;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
    BigInteger propA(*this);
    BigInteger propB(N);
    BigInteger product;
    BigInteger scalProd;
    if ( propA.sign() * propB.sign() == 0) {
        return product;
    }

    if(propA.sign() != propB.sign()){
        product.signum = -1;
    }else{
        product.signum = 1;
    }

    scalProd.signum = product.signum;

    List digitsA = propA.digits;
    List digitsB = propB.digits;
    List digitsProd;
    List scalarProd;

    digitsB.moveBack();
    long shift = 0;
    while(digitsB.position() > 0){
        long b = digitsB.peekPrev();
        digitsA.moveBack();
        long carry = 0;
        long prod;
        while(digitsA.position() > 0){
            long a = digitsA.peekPrev();
            prod = (a * b) + carry;
            carry = 0;
            while(prod >= BASE){
                prod -= BASE;
                carry += 1;
            }
            scalarProd.insertAfter(prod);
            digitsA.movePrev();
        }
        if (carry > 0) {
            scalarProd.insertAfter(carry);
        }
        if(shift > 0){
            scalarProd.moveBack();
            for(int i = 0; i < shift; i++){
                scalarProd.insertBefore(0);
            }
            scalProd.digits = scalarProd;
            product = product.add(scalProd);
            scalProd.digits.clear();
        }else{
            product.digits = scalarProd;
        }

        shift++;
        scalarProd.clear();
        digitsB.movePrev();
    }
    return product;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
    if(signum == 0){
        return "0";
    }
    std::string s = "";
    if(signum == -1){
        s += "-";
    }
    digits.moveFront();
    while(digits.position() < digits.length()){
        long curr = digits.moveNext();
        std::string curr_str = std::to_string(curr);

        while(digits.position() != 1 && curr_str.length() < POWER){
            curr_str = '0' + curr_str;
        }
        s += curr_str;
    }
    return s;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    // return stream << N.to_string();
	std::string s = "";
	if (N.signum == -1) {
		s += "-";
	} else if (N.signum == 0) {
		s += "0";
		stream << s;
		return stream;
	}

	int i = 0;
	N.digits.moveFront();

	for (i = 0; i < N.digits.length(); i++) {
		s += std::to_string(N.digits.peekNext());
		N.digits.moveNext();
	}

	stream << s;
	return stream;

}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
	List Ad = A.digits;
	List Bd = B.digits;
	if (A.signum != B.signum) {
		return false;
	}
	else {
		return A.digits.equals(B.digits);
	}
    /*BigInteger diff = A.sub(B);
    if(diff.digits.moveNext() == 0){
        return true;
    }else{
        return false;
    }*/
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    /*BigInteger diff = A.sub(B);
    if(diff.sign() < 0){
        return true;
    }else{
        return false;
    }*/
    List Ad = A.digits;
	List Bd = B.digits;
    long l,m;
	if ((A.signum == 0) && (B.signum == 0)) {
		return false;
	} else if ((A.signum < 0) && (B.signum >= 0)) {
		return true;
	} else if ((A.signum >=0 ) && (B.signum < 0)) {
		return false;
	} else if ((A.signum > 0) && (B.signum > 0)) {
		if (A.digits.length() < B.digits.length()) {
			return true;
		} else if (A.digits.length() > B.digits.length()) {
			return false;
		} else { // A.digits.length() == B.digits.length()
			if (A.digits.equals(B.digits)) {
				return false;
			}
			else {
				Bd.moveFront();
				for (Ad.moveFront(); Ad.position() < Ad.length(); Ad.moveNext()) {
					l = Ad.peekNext();
					m = Bd.peekNext();
					if (l > m) {
						return false;
					} else if (l < m) {
						return true;
					}
					Bd.moveNext();
				}
				return false;

			}
		}
	}
	else { //(A.signum < 0) && (B.signum < 0)
		if (A.digits.length() < B.digits.length()) {
			return false;
		}
		else if (A.digits.length() > B.digits.length()) {
			return true;
		}
		else { // A.digits.length() == B.digits.length()
			if (A.digits.equals(B.digits)) {
				return false;
			}
			else {
				Bd.moveFront();
				for (Ad.moveFront(); Ad.position() < Ad.length(); Ad.moveNext()) {
					l = Ad.peekNext();
					m = Bd.peekNext();
					if (l > m) {
						return true;
					}
					else if (l < m) {
						return false;
					}
					Bd.moveNext();
					//cout << m;
				}
				//cout << endl;
				return false;

			}
		}
	}
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    /*BigInteger diff = A.sub(B);
    if(diff.sign() <= 0){
        return true;
    }else{
        return false;
    }*/

    List Ad = A.digits;
	List Bd = B.digits;
	long l = 0, m = 0;
	if ((A.signum == 0) && (B.signum == 0)) {
		return true;
	}
	else if ((A.signum < 0) && (B.signum >= 0)) {
		return true;
	}
	else if ((A.signum >= 0) && (B.signum < 0)) {
		return false;
	}
	else if ((A.signum > 0) && (B.signum > 0)) {
		if (A.digits.length() < B.digits.length()) {
			return true;
		}
		else if (A.digits.length() > B.digits.length()) {
			return false;
		}
		else { // A.digits.length() == B.digits.length()
			if (A.digits.equals(B.digits)) {
				return true;
			}
			else {
				Bd.moveFront();
				for (Ad.moveFront(); Ad.position() < Ad.length(); Ad.moveNext()) {
					l = Ad.peekNext();
					m = Bd.peekNext();
					if (l > m) {
						return false;
					}
					else if (l < m) {
						return true;
					}
					Bd.moveNext();
					//cout << m;
				}
				//cout << endl;
				return true;

			}
		}
	}
	else { //(A.signum < 0) && (B.signum < 0)
		if (A.digits.length() < B.digits.length()) {
			return false;
		}
		else if (A.digits.length() > B.digits.length()) {
			return true;
		}
		else { // A.digits.length() == B.digits.length()
			if (A.digits.equals(B.digits)) {
				return true;
			}
			else {
				Bd.moveFront();
				for (Ad.moveFront(); Ad.position() < Ad.length(); Ad.moveNext()) {
					l = Ad.peekNext();
					m = Bd.peekNext();
					if (l > m) {
						return true;
					}
					else if (l < m) {
						return false;
					}
					Bd.moveNext();
					//cout << m;
				}
				//cout << endl;
				return true;

			}
		}
	}

}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
   /*BigInteger diff = A.sub(B);
    if(diff.sign() > 0){
        return true;
    }else{
        return false;
    }*/
    return !(A <= B);
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    /*BigInteger diff = A.sub(B);
    if(diff.sign() >= 0){
        return true;
    }else{
        return false;
    }*/
    return !(A < B);
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
   return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    A = A.add(B);
    return A.add(B);
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    A = A.sub(B);
    return A.sub(B);
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    A = A.mult(B);
    return A.mult(B);
}