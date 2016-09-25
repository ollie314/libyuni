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
#include <yuni/io/directory/info.h>
#include <iostream>

using namespace Yuni;



int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		std::cout << "usage: " << argv[0] << " [directory0] [directory1]...\n";
		return 0;
	}

	// Loop on all directories given as command line parameters
	for (int i = 1; i < argc; ++i)
	{
		// Get directory information
		IO::Directory::Info info(argv[i]);
		// Verify that the given path exists as a directory on the file system
		if (!info.exists())
		{
			std::cerr << "Invalid directory : \"" << argv[i] << "\"" << std::endl;
			// Ignore this path
			continue;
		}

		// Use a recursive iterator. It is used exactly as an STL iterator
		// All available iterators are :
		// * iterator, file_iterator, folder_iterator
		// * recursive_iterator, recursive_file_iterator, recursive_folder_iterator
		IO::Directory::Info::recursive_iterator end = info.recursive_end();
		for (IO::Directory::Info::recursive_iterator it = info.recursive_begin(); it != end; ++it)
		{
			// Check if it is a folder. isFile() also exists.
			if (it.isFolder())
			{
				std::cout << "[D] " << it.filename() << std::endl;
			}
			else
			{
				// For files, display the size (in bytes)
				std::cout
					<< "    " << it.filename()
					<< "  (" << it.size() << " bytes)" << std::endl;
			}
		}
	}
	return 0;
}

