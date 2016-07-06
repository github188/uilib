#pragma once

// System
#include <Windows.h>
#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <fstream>
#include <tchar.h>
#include <map>
#include <assert.h> 
#include <ctime>
#include "io.h"
#include "direct.h"

// Json
#include "document.h"
#include "prettywriter.h"
#include "stringbuffer.h"
#include "ostreamwrapper.h"
#include "istreamwrapper.h"

// Self
#include "AbstractVendor.h"
#include "QMSqlite.h"
#include "TestWindows.h"

using namespace rapidjson;

#define Test_Bug
#define Test_Filename

#define Vendor_JXJ	"佳信捷"
#define Vendor_DZP	"迪智普"

#define MAX_SEARCH_COUNT 1000
#define ONE_DAY		 (24 * 60 * 60)
#define ONE_HOUR	 (60 * 60)
#define ONE_MINUTE	 (60)

typedef enum
{
	Err_No = 0,
	Err_LoginSuccess, // Login Success
	Err_LoginFail,	// Login Fail
	Err_DownloadSuccess, // Download Success
}eErrCode;

struct RecordFile
{
	RecordFile()
	{
		channel = 0;
		size = 0;
		pPrivateData = nullptr;
		PrivateDataDataSize = 0;
	}
	~RecordFile()
	{
		if (nullptr != pPrivateData)
		{
			delete pPrivateData;
			pPrivateData = nullptr;
			PrivateDataDataSize = 0;
		}
	}
	RecordFile(const RecordFile& other)
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

	RecordFile& operator= (const RecordFile& other)
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

#include "j_sdk.h"

class CCommonUtrl
{
public:
	CCommonUtrl();
	~CCommonUtrl();

	static CCommonUtrl& getInstance();

	// File Name & File Folder
	std::string MakeDownloadFileFolder(const std::string basePath, const std::string& startTimeZero, const std::string& endTimeZero, const std::string& venderName, int channel);
	void MakeFolder(std::string fileName);

	// Video Time Range(JTime - JxjVendor)
	std::vector<time_range> MakeTimeRangeList(const time_range& range);
	void InitSearchTime(JTime& jStartTime, JTime& jStopTime, const __time64_t& timeStart, const __time64_t& timeEnd);
	time_t MakeTimestampByJTime(JTime jTime);
	std::string MakeStrTimeByTimestamp(time_t time);
	
	// Json File Handle
	void SaveSearchFileListToFile(const std::vector<RecordFile>& files);
	std::vector<RecordFile> LoadSearchFileListFromFile();

};


typedef struct STRU_CHANNEL_INFO
{
	int		iDeviceIndex;			//对应的设备的数组下标
	int		iChanIndex;			//监控通道号
	char	chChanName[100];	//本地通道结点名称

	int		iPicResolution;				//图片分辨率
	int		iPicQuality;				//图片质量
	LONG	lRealHandle;          //实时预览句柄

	int     iWinowIndex;           //预览时与通道关联的窗口索引
	BOOL    isRecording;           //正在录像
	BOOL    bEnable;               //通道是否使能
	char	chAccessChanIP[16];//ip接入通道的ip地址

	STRU_CHANNEL_INFO *pNext;

	STRU_CHANNEL_INFO()
	{
		iDeviceIndex = -1;
		iChanIndex = -1;
		chChanName[0] = '\0';
		iPicResolution = 0;
		iPicQuality = 2;
		lRealHandle = -1;
		chAccessChanIP[0] = '\0';
		iWinowIndex = -1;
		isRecording = FALSE;
		bEnable = FALSE;
		pNext = NULL;
	}
}CHANNEL_INFO, *pCHANNEL_INFO;

typedef struct STRU_DEVICE_INFO
{
	int		iDeviceIndex;			//设备数组下标
	LONG	lLoginID;				//注册ID
	char	chLocalNodeName[100];	//本地设备节点名称
	char	chDeviceName[100];		//设备名称
	char	chDeviceIP[33];			//可以直接连接的设备IP
	UINT	lDevicePort;			//设备主端口号
	char	chLoginUserName[30];	//登陆设备的用户名，在用户管理的时候用到
	char	chLoginPwd[30];	//登陆设备的密码
	//char	chDeviceMultiIP[20];	//多播组地址
	char	chSerialNumber[50];		//序列号
	int		iDeviceChanNum;		    //设备的通道数
	int		iStartChan;				//设备开始通道号
	int		iDeviceType;			//设备类型
	int 	iIPChanNum;				//最大数字通道个数
	BOOL    bIPRet;                 //是否IP接入
	//	BOOL	bCycle;					//该设备是否在循环播放
	BOOL	bPlayDevice;			//该设备是不是所有通道都在播放
	BOOL    bIsLogin;               //是否已注册该设备
	int		iEnableChanNum;			//有效通道数
	CHANNEL_INFO struChanInfo[64];
	STRU_DEVICE_INFO *pNext;

	STRU_DEVICE_INFO()
	{
		//  iDeviceIndex  = -1;
		lLoginID = -1;
		chLocalNodeName[0] = '\0';
		chDeviceName[0] = '\0';
		chDeviceIP[0] = '\0';
		lDevicePort = 8000;
		chLoginUserName[0] = '\0';
		chLoginPwd[0] = '\0';
		//chDeviceMultiIP[0]   ='\0';
		chSerialNumber[0] = '\0';
		iDeviceChanNum = -1;
		iStartChan = 0;
		iDeviceType = 0;
		iIPChanNum = 0;
		bIPRet = 0;
		bIsLogin = FALSE;
		//		 bCycle              = FALSE;
		bPlayDevice = FALSE;
		iEnableChanNum = -1;
		pNext = NULL;
	}
}LOCAL_DEVICE_INFO, *pLOCAL_DEVICE_INFO;