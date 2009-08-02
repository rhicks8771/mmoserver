/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2008 The swgANH Team

---------------------------------------------------------------------------------------
*/

#ifndef ANH_LOGMANAGER_H
#define ANH_LOGMANAGER_H

#include "Log.h"

#include "Utils/typedefs.h"
#include "zthread/ZThread.h"

#include <map>


//======================================================================================================================
#define gLogger	LogManager::getSingletonPtr()

typedef std::map<std::string,Log*,std::less<std::string> > LogList;


//======================================================================================================================
class LogManager
{
	public:
		static LogManager*  getSingletonPtr() { return mSingleton; }
		static LogManager*	Init(GlobalLogLevel glevel = G_LEVEL_NORMAL,const std::string& name = "default.log",LogLevel level = LEVEL_NORMAL,bool fileOut = true,bool consoleOut = false,bool append = false);
		static void         destroySingleton(void)  { delete mSingleton; mSingleton = 0; };

		~LogManager();

		Log*		  createLog(const std::string& name,LogLevel level = LEVEL_NORMAL,bool fileOut = true,bool consoleOut = false,bool append = false);
		Log*		  getLog(const std::string& name);
		Log*		  setDefaultLog(Log* log);
		Log*		  getDefaultLog(){ return mDefaultLog; }

		void		  logMsg(const std::string& msg, int Color);
		void		  logMsg(const std::string& logname,const std::string& msg,MsgPriority mp = MSG_NORMAL,bool fileOut = true,bool consoleOut = true,bool timestamp = true);
		void		  logMsg(Log* log,const std::string& msg,MsgPriority mp = MSG_NORMAL,bool fileOut = true,bool consoleOut = true,bool timestamp = true);
		void		  logMsg(const std::string& msg,MsgPriority mp = MSG_NORMAL,bool fileOut = true,bool consoleOut = true,bool timestamp = true, int Color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		void		  logMsgF(const std::string& msg, MsgPriority mp, ...);
		void		  logMsgF(Log* log, const std::string& msg, MsgPriority mp, ...);
		void		  hexDump(int8* data,uint32 len,MsgPriority mp = MSG_NORMAL);
		void		  hexDump(int8* data,uint32 len,const char* filename);

		void		  setLogLevel(const std::string& logname,LogLevel level);
		void		  setLogLevel(Log* log,LogLevel level);
		void		  setLogLevel(LogLevel level);

		void		  setGlobalLogLevel(GlobalLogLevel glevel);

	private:

		LogManager(GlobalLogLevel glevel,const std::string& name,LogLevel level,bool fileOut,bool consoleOut,bool append);

		static LogManager*	mSingleton;

		LogList				mLogs;
		Log*				mDefaultLog;
		GlobalLogLevel		mGlobalLogLevel;
		ZThread::Mutex      mGlobalLogMutex;
};

#endif