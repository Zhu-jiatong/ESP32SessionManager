#pragma once

#include <map>
#include <chrono>
#include <functional>

class Session
{
public:
	Session(const char* userId)
		:m_userId(userId), m_lastActiveTimestamp(std::chrono::high_resolution_clock::now()) {};
	const char* m_userId = nullptr;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_lastActiveTimestamp;
};

template<typename SessionType, typename KeyType>
class SessionManager
{
public:
	SessionManager(
		std::function<void(KeyType)> fn_storeSession,
		std::function<void(KeyType)> fn_deleteSession,
		std::function<void(KeyType)> fn_retrieveSession,
		std::function<bool()> fn_authenticateSession
	) :
		m_fn_storeSession(fn_storeSession),
		m_fn_deleteSession(fn_deleteSession),
		m_fn_retrieveSession(fn_retrieveSession),
		m_fn_authenticateSession(fn_authenticateSession)
	{}

	virtual void begin() = 0;
	virtual void createSession(uint32_t) = 0;
	virtual void terminateSession(KeyType) = 0;
	virtual void updateSessions() = 0;
	virtual SessionType getSessionInformation(KeyType) = 0;

protected:
	std::function<void(KeyType)> m_fn_storeSession;
	std::function<void(KeyType)> m_fn_deleteSession;
	std::function<void(KeyType)> m_fn_retrieveSession;
	std::function<bool()> m_fn_authenticateSession;
};
