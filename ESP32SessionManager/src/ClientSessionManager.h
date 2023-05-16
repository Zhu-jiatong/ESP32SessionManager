#pragma once
#include "SessionManagerInterface.h"
#include "ClientSession.h"
#include <functional>
#include <memory>
#include <type_traits>

template<typename ClientSessionType = ClientSession>
class ClientSessionManager :
	public SessionManagerBase<ClientSessionType>
{
public:
	using SessionManagerBase<ClientSessionType>::SessionManagerBase;
	using session_type = typename SessionManagerBase<ClientSessionType>::session_type;
	using key_type = typename SessionManagerBase<ClientSessionType>::key_type;

	void begin();
	void updateSessions();
	void createSession(session_type sessionData);
	void terminateSession(key_type sessionId);
	ClientSessionType getSessionInformation(key_type sessionId); // TODO: use `std::optional`

	static std::string sessionIdToString(key_type sessionId);
	static std::shared_ptr<uint8_t[32]> sessionIdToArray(std::string sessionIdString);

private:
	std::shared_ptr<uint8_t[32]> generateId(uint32_t clientIpAddress);
	std::chrono::time_point<std::chrono::high_resolution_clock> initialTimestamp;
};

#include "ClientSessionManagerImpl.h"