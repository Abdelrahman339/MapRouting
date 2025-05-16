#include <iostream>
#include "../A_Star/A_Star.h"
#include "../File/File.h"
#include <chrono>
using namespace std::chrono;
using namespace std;


class test
{
public:
	void  visual();
	void  displayTest(char choice);
	char  simpleTest();
	void  bounsTest();
	bestPath  doTest(char choice);

};