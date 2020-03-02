//
// t2Test.cpp
//
// Copyright (C) 2012 - 2017 jones@scss.tcd.ie
//
// 09/10/17	first version
//

//#include "stdafx.h"			// pre-compiled headers
#include "pch.h"
#include <iostream>			// cout
#include <conio.h>			// _getch
#include "fib64.h"			//
#include "t2.h"	
#include "tchar.h"

using namespace std;		// cout

//
// fib: C++
//
_int64 fib(_int64 n) {
	_int64 fi, fj, t;
	if (n <= 1)
		return n;
	fi = 0;
	fj = 1;
	while (n > 1) {
		t = fj;
		fj = fi + fj;
		fi = t;
		n--;
	}
	return fj;
}

//
// check
//
void check(const char *s, _int64 v, _int64 expected) {
	cout << s << " = " << v;
	if (v == expected) {
		cout << " OK";
	}
	else {
		cout << " ERROR: should be " << expected;
	}
	cout << endl;
}

//
// _tmain
//
int _tmain(int argc, _TCHAR* argv[]) {

	min(1, 2, 3);

	//
	// tutorial 2
	//
	check("g", g, 4);
	g++;
	check("g", g, 5);
	g--;
	check("g", g, 4);

	check("min(1, 2, 3)", min(1, 2, 3), 1);
	check("min(3, 1, 2)", min(3, 1, 2), 1);
	check("min(2, 3, 1)", min(2, 3, 1), 1);
	check("min(-1, -2, -3)", min(-1, -2, -3), -3);
	check("min(-3, -1, -2)", min(-3, -1, -2), -3);
	check("min(-2, -3, -1)", min(-2, -3, -1), -3);
	check("min(-1, 2, 3)", min(-1, 2, 3), -1);
	check("min(3, -1, 2)", min(3, -1, 2), -1);
	check("min(2, 3, -1)", min(2, 3, -1), -1);

	check("p(0, 1, 2, 3)", p(0, 1, 2, 3), 0);
	check("p(5, 6, 7, 8)", p(5, 6, 7, 8), 4);
	check("p(3, 2, 1, 0)", p(3, 2, 1, 0), 0);
	check("p(8, 7, 6, 5)", p(8, 7, 6, 5), 4);

	check("gcd(14, 21)", gcd(14, 21), 7);
	check("gcd(1406700, 164115)", gcd(1406700, 164115), 23445);

	check("q(1, 2, 3, 4, 5)", q(1, 2, 3, 4, 5), 15);
	check("q(-1, 2, -3, 4, -5)", q(-1, 2, -3, 4, -5), -3);

	//check("qns()", qns(), 0);

	cout << endl;

	//
	// fib: C++
	//
	for (int i = -1; i < 20; i++)
		cout << fib(i) << " ";
	cout << endl;

	//
	// fib: x64 assembly language
	//
	fibX64(10);
	for (int i = -1; i < 20; i++)
		cout << fibX64(i) << " ";
	cout << endl;

	_getch();

	return 0;

}

// eof