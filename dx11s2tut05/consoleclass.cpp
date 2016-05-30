#include "consoleclass.h"

ConsoleClass::ConsoleClass()
{
	//m_Font = 0;
	//m_FontShader = 0;
	//m_sentence1 = 0;
}


ConsoleClass::ConsoleClass(const ConsoleClass& other)
{
}


ConsoleClass::~ConsoleClass()
{
}

bool ConsoleClass::Initialize(){

	//inizializzo lo spazio per 50 elementi
	m_messages.reserve(50);

	return true;
}


void ConsoleClass::Shutdown()
{
	/*
	// Release the first sentence.
	ReleaseSentence(&m_sentence1);

	// Release the font shader object.
	if (m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}

	// Release the font object.
	if (m_Font)
	{
		m_Font->Shutdown();
		delete m_Font;
		m_Font = 0;
	}*/

	return;
}

void ConsoleClass::appendMessage(std::string s){

	std::string number = std::to_string(m_messages.size());

	m_messages.push_back(number + "  " +s);
}

std::string ConsoleClass::getMessage(int index){

	return m_messages[index];
}

int ConsoleClass::getNumberOfMessages(){

	return m_messages.size();
}
