/*
** This file is part of libyuni, a cross-platform C++ framework (http://libyuni.org).
**
** This Source Code Form is subject to the terms of the Mozilla Public License
** v.2.0. If a copy of the MPL was not distributed with this file, You can
** obtain one at http://mozilla.org/MPL/2.0/.
**
** github: https://github.com/libyuni/libyuni/
** gitlab: https://gitlab.com/libyuni/libyuni/ (mirror)
*/
#include <yuni/yuni.h>
#include <yuni/core/getopt.h>
#include <iostream>


using namespace Yuni;


/*
** How to try the example from the command line :
**
** To Display the help :
** ./getopt_00_simple -h
** ./getopt_00_simple --help
** ./getopt_00_simple /?      (Windows only)
** ./getopt_00_simple /help   (Windows only)
**
** To test the example of an option :
** ./getopt_00_simple --text="Lorem Ipsum" --int=13
** ./getopt_00_simple --text "Lorem Ipsum" --int 13
** ./getopt_00_simple -t "Lorem Ipsum"
** ./getopt_00_simple /text "Lorem Ipsum" /int 13 (Windows only)
** ./getopt_00_simple /t "Lorem Ipsum" /int 13    (Windows only)
**
** You can try an unknown option :
** ./getopt_00_simple --unknown-option
*/



int main(int argc, char* argv[])
{
	// The command line options parser
	GetOpt::Parser options;

	// Option : --text="<X>" or -t "<X>"
	String optText = "A default value";
	options.add(optText, 't', "text", "An example with the type `Yuni::String`");

	// Option : --int="<X>" or -i "<X>"
	int optInt = 42;
	options.add(optInt, 'i', "int", "An example with the type `int`");

	// Ask to the parser to parse the command line
	if (!options(argc, argv))
	{
		// The program should not continue here
		return (options.errors() ? 1 /* error */ : 0);
	}

	// Displaying the values
	std::cout << "Value for `optText` : `" << optText << "`" << std::endl;
	std::cout << "Value for `optInt`  : `" << optInt << "`" << std::endl;

	return 0;
}
