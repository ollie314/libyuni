/*
** YUNI's default license is the GNU Lesser Public License (LGPL), with some
** exclusions (see below). This basically means that you can get the full source
** code for nothing, so long as you adhere to a few rules.
**
** Under the LGPL you may use YUNI for any purpose you wish, and modify it if you
** require, as long as you:
**
** Pass on the (modified) YUNI source code with your software, with original
** copyrights intact :
**  * If you distribute electronically, the source can be a separate download
**    (either from your own site if you modified YUNI, or to the official YUNI
**    website if you used an unmodified version) – just include a link in your
**    documentation
**  * If you distribute physical media, the YUNI source that you used to build
**    your application should be included on that media
** Make it clear where you have customised it.
**
** In addition to the LGPL license text, the following exceptions / clarifications
** to the LGPL conditions apply to YUNI:
**
**  * Making modifications to YUNI configuration files, build scripts and
**    configuration headers such as yuni/platform.h in order to create a
**    customised build setup of YUNI with the otherwise unmodified source code,
**    does not constitute a derived work
**  * Building against YUNI headers which have inlined code does not constitute a
**    derived work
**  * Code which subclasses YUNI classes outside of the YUNI libraries does not
**    form a derived work
**  * Statically linking the YUNI libraries into a user application does not make
**    the user application a derived work.
**  * Using source code obsfucation on the YUNI source code when distributing it
**    is not permitted.
** As per the terms of the LGPL, a "derived work" is one for which you have to
** distribute source code for, so when the clauses above define something as not
** a derived work, it means you don't have to distribute source code for it.
** However, the original YUNI source code with all modifications must always be
** made available.
*/
#include <yuni/yuni.h>
#include <yuni/core/getopt.h>
#include <iostream>


using namespace Yuni;


/*
** This sample shows how to write its own help usage
** from scratch.
** If you only want to add some text paragraph, please refer to `03.paragraph`
*/


/*
** How to try the example from the command line :
**
** To Display the help :
** ./getopt_04_customhelpusage -h
** ./getopt_04_customhelpusage --help
** ./getopt_04_customhelpusage /?      (Windows only)
** ./getopt_04_customhelpusage /help   (Windows only)
*/



int main(int argc, char* argv[])
{
	// The command line options parser
	GetOpt::Parser options;

	// A simple option : --text
	String optText;
	options.add(optText, 't', "text");

	// For the help, we want to display _our_ help usage
	// For that, we have to override the option `--help`
	bool optHelp = false;
	options.addFlag(optHelp, 'h', "help");

	// But, do not forget to do the same thing for `?` on
	// Windows, for compatibility with other programs.
	// Example: getopt_04_customhelpusage.exe /?
	# ifdef YUNI_OS_WINDOWS
	// It is safe to use the same variable `optFlag`
	options.addFlag(optHelp, '?');
	# endif


	// Ask the parser to parse the command line
	if (!options(argc, argv))
	{
		// The program should not continue here
		return (options.errors() ? 1 /* error */ : 0);
	}


	if (optHelp)
	{
		std::cout <<
			"This is our custom help usage.\n"
			"Here is the list of options :\n\n"
			" -t, --text=VALUE : A text to display\n\n";
		return 0;
	}

	std::cout << "Text : `" << optText << "`" << std::endl;

	return 0;
}
