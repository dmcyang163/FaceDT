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

	static string getIpAddress(string type = "eth0");

	static string DoubleToString(double Input);
	static double StringToDouble(string Input);
};