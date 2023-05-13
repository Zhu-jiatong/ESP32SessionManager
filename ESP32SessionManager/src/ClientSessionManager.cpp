#include "ClientSessionManager.h"
#include <sstream>
#include <cstring>
#include <string>
#include <mbedtls/sha256.h>
#include <iostream>

ClientSessionManager::ClientSessionManager(
	std::function<void(ClientSession, uint8_t*)> fn_storeSession,
	std::function<void(uint8_t*)> fn_deleteSession,
	std::function<void(uint8_t*)> fn_retrieveSession,
	std::function<bool()> fn_authenticateSession
)
	: SessionManager{ fn_storeSession, fn_deleteSession, fn_retrieveSession, fn_authenticateSession }
{
}

void ClientSessionManager::begin()
{
}

void ClientSessionManager::updateSessions()
{
}

void ClientSessionManager::createSession(uint32_t clientIpAddress)
{
	std::shared_ptr<uint8_t[32]> sessionId = generateId(clientIpAddress);
	ClientSession sessionData("hello");
	m_fn_storeSession(sessionData, sessionId.get());
}

void ClientSessionManager::terminateSession(uint8_t* sessionId)
{
	m_fn_deleteSession(sessionId);
}

ClientSession ClientSessionManager::getSessionInformation(uint8_t* sessionId)
{
	m_fn_retrieveSession;
	return ClientSession("Random");
}

std::shared_ptr<uint8_t[32]> ClientSessionManager::generateId(uint32_t clientIpAddress)
{
	std::shared_ptr<uint8_t[32]> output(new uint8_t[32], std::default_delete<uint8_t[]>());

	auto timestamp = std::chrono::high_resolution_clock::now();
	auto period = std::chrono::duration_cast<std::chrono::nanoseconds>(timestamp - initialTimestamp).count();

	std::ostringstream ss;
	ss << period << clientIpAddress;
	const std::string& inputStr = ss.str();
	const char* inputCstr = inputStr.c_str();
	std::cout << inputCstr << '\n';
	mbedtls_sha256_ret(reinterpret_cast<const uint8_t*>(inputCstr), strlen(inputCstr), output.get(), 0);
	return output;
}
