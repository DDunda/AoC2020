// Day 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Input.h"
#include <chrono>

#include <algorithm>

using namespace std;
using namespace chrono;
typedef steady_clock SC;

/*
int input[] = {
	1711,
	1924,
	1384,
	1590,
	1876,
	1918,
	2003,
	1514,
	1608,
	1984,
	1706,
	1375,
	1476,
	1909,
	1615,
	1879,
	1940,
	1945,
	1899,
	1510,
	1657,
	1685,
	1588,
	1884,
	1864,
	1995,
	1648,
	1713,
	1532,
	1556,
	1572,
	1667,
	1861,
	1773,
	1501,
	1564,
	1756,
	395 ,
	1585,
	1717,
	1553,
	1487,
	1617,
	1808,
	1780,
	1570,
	1881,
	1992,
	1894,
	1772,
	1837,
	2002,
	1659,
	1731,
	1873,
	1760,
	552 ,
	1575,
	1597,
	1986,
	1416,
	1398,
	1737,
	1027,
	1457,
	198 ,
	1904,
	1753,
	1727,
	633 ,
	1577,
	1944,
	1369,
	1400,
	1843,
	1966,
	1008,
	1681,
	1890,
	1939,
	1605,
	1548,
	1953,
	1839,
	1409,
	1592,
	1744,
	1761,
	1613,
	1412,
	1759,
	703 ,
	1498,
	1941,
	1425,
	1528,
	1469,
	1728,
	1447,
	1406,
	1797,
	1543,
	1682,
	1722,
	1723,
	1893,
	1644,
	796 ,
	1505,
	1715,
	1729,
	1943,
	1626,
	1602,
	1964,
	1509,
	1816,
	1660,
	1399,
	1996,
	1750,
	1701,
	1963,
	1979,
	1558,
	1506,
	1465,
	2001,
	1935,
	1616,
	1990,
	1946,
	1818,
	1892,
	1431,
	1832,
	1688,
	2004,
	1424,
	1716,
	1897,
	1931,
	1557,
	1389,
	1872,
	1640,
	1670,
	1911,
	1427,
	1730,
	211 ,
	1420,
	1488,
	1689,
	1383,
	1967,
	1594,
	642 ,
	1622,
	1627,
	1607,
	1372,
	1596,
	1451,
	1693,
	1380,
	1745,
	1908,
	1785,
	1646,
	1824,
	1418,
	1258,
	1664,
	1631,
	1459,
	1901,
	1838,
	1794,
	1815,
	1388,
	1809,
	1920,
	1411,
	1593,
	1676,
	1610,
	1629,
	1512,
	1522,
	1649,
	1740,
	1695,
	1504,
	1856,
	1791,
	1898,
	1661,
	1806,
	1851
};
*/

#define ONE 1
#define TWO 2
#define PART TWO

void main()
{
	SC::time_point point1 = SC::now();
	int l = sizeof(input) / sizeof(int);

	/*qsort(
		input, 
		l, 
		sizeof(int), 
		[](const void* a, const void* b) -> int {
			return *(int*)a - *(int*)b;
		}
	);*/

	sort(input, input + l);

	SC::time_point point2 = SC::now();
	cout << "sort complete" << endl;

	int third;
	int lower;
	int upper;
	for (third = 0; third < l; third++) {
		long long psum = 2020 - input[third];

		int lower = 0;
		int upper = l - 1;

		if (upper == third) upper--;
		if (lower == third) lower++;

		while (lower < upper) {
			int sum = input[lower] + input[upper];
			if (sum > psum) {
				upper--;
				if (upper == third) upper--;
			}
			else if (sum < psum) {
				lower++;
				if (lower == third) lower++;
			}
			else {
				SC::time_point point3 = SC::now();
				cout << input[lower] << " " << input[upper] << " " << input[third] << endl;
				cout << (long long)input[lower] * (long long)input[upper] * (long long)input[third] << endl;
				cout << "Time for sort: " << (duration_cast<duration<double>>(point2 - point1)).count() * 1000.0 << "ms" << endl;
				cout << "Time for solution: " << (duration_cast<duration<double>>(point3 - point2)).count() * 1000.0 << "ms" << endl;
				return;
			}
		}
	}
}