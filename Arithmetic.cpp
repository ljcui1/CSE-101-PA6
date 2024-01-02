//-----------------------------------------------------------------------------
// Name: Lia Cui
// CRUZID: ljcui
// Assignment Name: PA6
//
//-----------------------------------------------------------------------------

#include <fstream>
#include <string>
#include <iostream>
#include"BigInteger.h"
#include"List.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s input output\n", argv[0]);
		exit(1);
	}

	ifstream infile;
	ofstream outfile;
	infile.open(argv[1]);
	outfile.open(argv[2]);

	string sbuff;

	infile >> sbuff;
	BigInteger A = BigInteger(sbuff);
	infile >> sbuff;
	BigInteger B = BigInteger(sbuff);

	outfile << A << endl;
	outfile << endl;
	outfile.flush();
	outfile << B << endl;
	outfile << endl;
	outfile.flush();
	outfile << A + B << endl;
	outfile << endl;
	outfile.flush();
	outfile << A - B << endl;
	outfile << endl;
	outfile.flush();
	outfile << A - A << endl;
	outfile << endl;
	outfile.flush();
	outfile << 3*A - 2*B << endl;
	outfile << endl;
	outfile.flush();
	outfile << A * B << endl;
	outfile.flush();
	outfile << endl;
	outfile << A * A << endl;
	outfile.flush();
	outfile << endl;
	outfile << B * B << endl;
	outfile.flush();
	outfile << endl;
	outfile << 9*A*A*A*A + 16 * B*B*B*B*B << endl;
	outfile << endl;
	outfile.flush();

	infile.close();
	outfile.close();
	return(0);
}

