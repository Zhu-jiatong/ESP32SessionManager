/*
 Name:		Interfacing_with_C___Standard_Containers.ino
 Created:	5/16/2023 10:19:57 PM
 Author:	jiaji
*/

#include "ClientSessionManager.h"
#include <iostream>
#include <unordered_map>
#include <sstream>

std::unordered_map<std::string, ClientSession> sessions;

void storeSession(ClientSession sessionData);
void deleteSession(ClientSessionManager<>::key_type sessionId);
ClientSession retrieveSession(ClientSessionManager<>::key_type sessionId);

ClientSessionManager<> sessionManager(storeSession, deleteSession, retrieveSession);

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	std::cout << "Starting test\n";

	sessionManager.begin();

	ClientSession session1(12345, "Test User 1");
	ClientSession session2(67890, "Test User 2");
	ClientSession session3(13579, "Test User 3");

	sessionManager.createSession(session1);
	sessionManager.createSession(session2);
	sessionManager.createSession(session3);

	std::cout << "Setup complete, ready to accept user input\n";
}

// the loop function runs over and over again until power down or reset
void loop() {

}

void serialEvent()
{
	std::string hashString;

	while (Serial.available())
		hashString += static_cast<char>(Serial.read());

	auto querry = ClientSessionManager<>::sessionIdToArray(hashString);

	std::string sessionId = ClientSessionManager<>::sessionIdToString(querry.get());
	ClientSession session = sessionManager.getSessionInformation(querry.get());
	std::cout << session.m_userId << '\n';
}

void storeSession(ClientSession sessionData)
{
	std::string sessionId = ClientSessionManager<>::sessionIdToString(sessionData.m_sessionId.get());
	std::cout << "Stored Session: \"" << sessionData.m_userId << "\" with ID: \"" << sessionId << "\"\n";
	sessions.emplace(sessionId, sessionData);
}

void deleteSession(ClientSessionManager<>::key_type sessionId)
{
	std::cout << "Delete Session: " << ClientSessionManager<>::sessionIdToString(sessionId) << '\n';
}

ClientSession retrieveSession(ClientSessionManager<>::key_type sessionId)
{
	ClientSession& thisSession = sessions.at(ClientSessionManager<>::sessionIdToString(sessionId));
	return thisSession;
}
