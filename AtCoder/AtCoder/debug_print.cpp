//This source code is under the MIT License, see LICENSE.txt.
#include "debug_print.hpp"

namespace debug::print::detail
{
	std::ostream& operator<<(std::ostream& os, endl_t const&)
	{
		return (os << std::endl);
	}

	void write(std::ostream&)
	{

	}
}
