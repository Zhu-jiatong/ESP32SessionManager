#pragma once

#include "SessionManagerInterface.h"
#include <memory>

class ClientSession : public Session<uint8_t*>
{
public:
	ClientSession(uint32_t m_clientIP, const char* userId, std::shared_ptr<uint8_t[32]> sessionId = nullptr) :
		Session(userId, m_clientIP), m_sessionId(sessionId) {}

	std::shared_ptr<uint8_t[32]> m_sessionId;
};
