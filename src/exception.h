#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
/**
 *  Exception
 */
class Exception
{
	string message;

public:
	/**
	 * constructor
	 */
	Exception(string message): message(message) {}
	/**
	 * @return the Exception message
	 */
	string getMessage()
	{
		return message;
	}

};
#endif