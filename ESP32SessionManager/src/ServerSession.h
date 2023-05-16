#pragma once
#include "SessionManagerInterface.h"

struct ServerSession :
	public Session<uint32_t>
{
};

