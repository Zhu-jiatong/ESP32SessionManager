/*
 Name:		BasicExample.ino
 Created:	4/25/2023 3:11:59 PM
 Author:	jiaji
*/

#include "ClientSessionManager.h"
#include <iostream>
#include <iomanip>

void storeSession(uint8_t* sessionId);
void deleteSession(uint8_t* sessionId);
void retrieveSession(uint8_t* sessionId);
bool authentiacateSession();

ClientSessionManager sessions(storeSession, deleteSession, retrieveSession, authentiacateSession);

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	std::cout << "Starting test\n";

	sessions.begin();
	sessions.createSession(123456);

	std::cout << "end test\n";
}

// the loop function runs over and over again until power down or reset
void loop() {

}

void storeSession(uint8_t* sessionId)
{
	std::cout << "Store Session: ";
	for (size_t i = 0; i < 32; ++i)
		printf("%02x", sessionId[i]);
	std::cout << '\n';
	std::cout << "Store Session: ";
	for (size_t i = 0; i < 32; ++i)
		std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)sessionId[i];
	std::cout << '\n';
}

void deleteSession(uint8_t* sessionId)
{
	std::cout << "Delete Session: " << std::hex << sessionId << '\n';
}

bool authentiacateSession()
{
	return true;
}

void retrieveSession(uint8_t* sessionId)
{
	std::cout << "retrieveSession\n";
}