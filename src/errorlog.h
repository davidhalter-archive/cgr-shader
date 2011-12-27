/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#ifndef _ERRORLOG_H
#define	_ERRORLOG_H
//--------------------------------------------------
#include "global.h"
#include <string>
#include <fstream>          // to write files
#include <string>
//--------------------------------------------------
/**
 * This class logs all errors that appear during program execution
 * in an error log file. The class is constructed as a singleton
 */
class ErrorLog
{
private:
	static ErrorLog *instance;
	ErrorLog();
	fstream file;
public:
	/**
	 * Returns a valid ErrorLog instance
	 * @return pointer to an ErrorLog instance
	 */
	static ErrorLog *getInstance();
	/**
	 * This method takes an error message as an argument and stores
	 * the message in the log file.
	 * @param errorMessage Message to be stored in error log file
	 */
	void reportError(string errorMessage);
	/**
	 * destructor
	 */
	~ErrorLog();
};
//--------------------------------------------------
#endif	/* _ERRORLOG_H */
