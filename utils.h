#pragma once

#include <iostream>
using namespace std;


class CUtils
{
public:
	CUtils();
	virtual ~CUtils();

	static string getPath(string filename = "");

	static string getCpuid();
	static bool isCpuMatch(string cpuid);

};