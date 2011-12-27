/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#include "errorlog.h"
//--------------------------------------------------
// define static variable
ErrorLog *ErrorLog::instance = NULL;
//--------------------------------------------------
ErrorLog::ErrorLog()
{
	file.open("errorLog.txt", ios::out);
	file << "Error Log File:" << endl;
	file << "---------------------------" << endl;
	file.close();
}
//--------------------------------------------------
ErrorLog *ErrorLog::getInstance()
{
	if (instance == NULL)
	{
		instance = new ErrorLog();
	}
	return instance;
}
//--------------------------------------------------
void ErrorLog::reportError(string errorMessage)
{
	// create a c++ stream and write string to file
	file.open("errorLog.txt", ios::out | ios::app);
	file << errorMessage << endl;
	file.close();
}
//--------------------------------------------------
ErrorLog::~ErrorLog()
{
	if (instance != NULL)
	{
		instance = NULL;
		delete instance;
	}
}
//--------------------------------------------------
