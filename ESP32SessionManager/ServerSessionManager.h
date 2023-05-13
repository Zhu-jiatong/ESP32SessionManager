#pragma once

#include "SessionManagerInterface.h"
#include "ServerSession.h"

class ServerSessionManager :
    private SessionManager<ServerSession, const char*>
{
};
