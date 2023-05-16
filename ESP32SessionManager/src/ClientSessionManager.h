#pragma once
#include "SessionManagerInterface.h"
#include "ClientSession.h"
#include <functional>
#include <memory>

class ClientSessionManager :
	public SessionManager<ClientSession, ClientSession::key_type>
{
public:
	using SessionManager::SessionManager;
	void begin();
	void updateSessions();
	void createSession(ClientSession sessionData);
	void terminateSession(ClientSession::key_type sessionId);
	ClientSession getSessionInformation(ClientSession::key_type sessionId); // TODO: use `std::optional`

	static std::string sessionIdToString(key_type sessionId);
	static std::shared_ptr<uint8_t[32]> sessionIdToArray(std::string sessionIdString);

private:
	std::shared_ptr<uint8_t[32]> generateId(uint32_t clientIpAddress);
	std::chrono::time_point<std::chrono::high_resolution_clock> initialTimestamp;
};
