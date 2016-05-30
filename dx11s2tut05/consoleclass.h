////////////////////////////////////////////////////////////////////////////////
// Filename: consoleclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _CONSOLECLASS_H_
#define _CONSOLECLASS_H_

#include <vector>
#include <string>
#include <directxmath.h>
using namespace DirectX;

const int MAX_MESSAGES_SHOWN = 16;

class ConsoleClass
{
public:

	ConsoleClass();
	ConsoleClass(const ConsoleClass&);
	~ConsoleClass();

	bool Initialize();
	void Shutdown();

	void appendMessage(std::string);
	std::string getMessage(int);

	int getNumberOfMessages();

private:

	std::vector<std::string> m_messages;
	

};

#endif