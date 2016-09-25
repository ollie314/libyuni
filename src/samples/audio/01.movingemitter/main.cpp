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
#include <vector>
#include <yuni/yuni.h>
#include <yuni/media/queueservice.h>
#include <yuni/core/system/suspend.h>
#include <yuni/core/math.h>

using namespace Yuni;





int main(int argc, char* argv[])
{
	// Trivial command line parsing
	if (argc < 2)
	{
		std::cout << "usage: " << argv[0] << " <filename>" << std::endl;
		return EXIT_FAILURE;
	}
	AnyString filename = argv[1];


	// Media manager
	Media::QueueService media;
	media.start();

	if (!media.running())
		return 1;

	static const float LIMIT = 150.0f;

	// adding a new emitter
	AnyString emitterName("Emitter");
	if (not media.emitter.add(emitterName))
	{
		std::cerr << "Emitter creation failed !" << std::endl;
		return EXIT_FAILURE;
	}

	// loading the sound in the sound library
	if (not media.library.load(filename))
	{
		std::cerr << "impossible to load " << filename << std::endl;
		return EXIT_FAILURE;
	}

	// attaching it to our emitter
	media.emitter.attach(emitterName, filename);
	media.emitter.play(emitterName);

	if (media.library.channels(filename) > 1)
		std::cerr << "Warning : 3D sound only works with mono sources !" << std::endl;

	// emitter position
	Point3D<> position; // [0, 0, 0]
	bool inverse = false;
	position.y = -LIMIT;
	media.emitter.move(emitterName, position);

	for (uint i = 0; i < 2000; ++i) // arbitrary
	{
		// pause
		SuspendMilliSeconds(50); // milliseconds (arbitrary)

		// Moving the emitter around us
		position.y += 1.0f * (inverse ? -1.0f : 1.0f);

		if (!inverse && position.y > LIMIT)
		{
			inverse = true;
		}
		else
		{
			if (inverse && position.y < -LIMIT)
				inverse = false;
		}
		media.emitter.move(emitterName, position);
	}

	return 0;
}

