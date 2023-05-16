#pragma once
#include "SessionManagerInterface.h"

class ServerSession :
    public SessionManager<ServerSession, uint32_t>::Session
{
};

