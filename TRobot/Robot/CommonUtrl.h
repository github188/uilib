#pragma once

// System
#include <Windows.h>
#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <fstream>
#include <tchar.h>
#include "io.h"
#include "direct.h"

// Jxj SDK
#include "inc\mb_api.h"
#include "inc\JNetSDK.h"
#include "inc\stdint.h"
#include "inc\Jtype.h"
#include "inc\AVPlayer.h"

// Json
#include "document.h"
#include "prettywriter.h"
#include "stringbuffer.h"
#include "ostreamwrapper.h"
#include "istreamwrapper.h"

#include "AbstractVendor.h"
#include "TestWindows.h"
#include "QMSqlite.h"

#define Test_Bug
#define Test_Filename

typedef enum
{
	Err_No = 0,
	Err_LoginSuccess, // Login Success
	Err_LoginFail,	// Login Fail
	Err_DownloadSuccess, // Download Success
}eErrCode;

struct Record
{
	Record()
	{
		channel = 0;
		size = 0;
		pPrivateData = nullptr;
		PrivateDataDataSize = 0;
	}
	~Record()
	{
		if (nullptr != pPrivateData)
		{
			delete pPrivateData;
			pPrivateData = nullptr;
			PrivateDataDataSize = 0;
		}
	}
	Record(const Record& other)
	{
		channel = other.channel;
		size = other.size;
		name = other.name;
		//alias = other.alias;
		strTimeSection = other.strTimeSection;
		beginTime = other.beginTime;
		endTime = other.endTime;
		duration = other.duration;
		pPrivateData = nullptr;
		PrivateDataDataSize = 0;
		setPrivateData(other.pPrivateData, other.PrivateDataDataSize);
	}

	Record& operator= (const Record& other)
	{
		if (&other == this)
		{
			return *this;
		}
		channel = other.channel;
		size = other.size;
		name = other.name;
		//alias = other.alias;
		strTimeSection = other.strTimeSection;
		beginTime = other.beginTime;
		endTime = other.endTime;
		duration = other.duration;
		setPrivateData(other.pPrivateData, other.PrivateDataDataSize);
		return *this;
	}
	// Set Private Data
	void setPrivateData(void* pData, int size)
	{
		if (nullptr != pPrivateData)
		{
			delete pPrivateData;
			pPrivateData = nullptr;
			PrivateDataDataSize = 0;
		}
		if (size > 0)
		{
			pPrivateData = new char[size];
			PrivateDataDataSize = size;
			memcpy(pPrivateData, pData, size);
		}
	}
	// Get Private Data
	void* getPrivateData() const
	{
		return pPrivateData;
	}
	// Get Private Data Size
	__int32 getPrivateDataSize() const
	{
		return PrivateDataDataSize;
	}
	void deletePrivateData()
	{
		delete pPrivateData;
		pPrivateData = nullptr;
	}

	int channel;
	int size;
	std::string name;
	//std::string alias;
	std::string strTimeSection;
	std::time_t beginTime;
	std::time_t endTime;
	unsigned long duration;
	char* pPrivateData;   //Private Data
	__int32 PrivateDataDataSize;//Private Data Size
};

class CCommonUtrl
{
public:
	CCommonUtrl();
	~CCommonUtrl();

	static CCommonUtrl& getInstance();

	// File Name & File Folder
	std::string MakeFileName(int channel, const std::string& startTime, const std::string& endTime);
	std::string MakeDownloadFileFolder(const std::string basePath, const std::string& startTimeZero, const std::string& endTimeZero, const std::string& venderName, int channel);
	void MakeFolder(std::string fileName);

	// Video Time Range(JTime - JxjVendor)
	std::vector<time_range> MakeTimeRangeList(const time_range& range);
	void InitSearchTime(JTime& jStartTime, JTime& jStopTime, const __time64_t& timeStart, const __time64_t& timeEnd);
	time_t MakeTimestampByJTime(JTime jTime);
	std::string MakeStrTimeByTimestamp(time_t time);
	
	// Json File Handle
	void SaveSearchFileListToFile(const std::vector<Record>& files);
	std::vector<Record> LoadSearchFileListFromFile();

};

