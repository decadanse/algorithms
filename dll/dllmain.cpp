// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
//#include "stdafx.h"
#include <math.h>
#include <string>
#include <stdexcept>
#include <Windows.h>
#include <stdio.h>

using namespace std;

double someone_func(double x, double a, double epsilon) {
	int k = 0;
	double sum = 2;
	double next = 1;

	int d = 2;
		
	do {				
		sum -= next;	
		next = - (next * x) / d;
		d += 2;
		k++;

	} while (fabs(next) >= epsilon);

	return sum;
}

extern "C" __declspec(dllexport) double myf_1b(double x, double a, double eps, double(*func))//prav
{	
	return (someone_func(x, a, eps));
}

extern "C" __declspec(dllexport) double myf_math(double x, double a)//lev
{
	return sqrt(1 + x);
}

extern "C" __declspec(dllexport) const char* FName()
{	
	return "sqrt(1 + x)";
}
