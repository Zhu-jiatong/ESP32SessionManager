#pragma once

#include "SessionManagerInterface.h"
#include "ServerSession.h"

class ServerSessionManager :
    private SessionManagerBase<ServerSession, const char*>
{
};
