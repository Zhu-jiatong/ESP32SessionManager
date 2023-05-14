#pragma once
#include "SessionManagerInterface.h"
#include "ClientSession.h"
#include <functional>
#include <memory>

class ClientSessionManager :
	public SessionManager<ClientSession, uint8_t*>
{
public:
	using SessionManager::SessionManager;
	void begin();
	void updateSessions();
	void createSession(uint32_t clientIpAddress);
	void terminateSession(uint8_t* sessionId);
	ClientSession getSessionInformation(uint8_t* sessionId);

private:
	std::shared_ptr<uint8_t[32]> generateId(uint32_t clientIpAddress);
	std::chrono::time_point<std::chrono::high_resolution_clock> initialTimestamp;
};
