#pragma once

enum ENCODE{ FLV, MP4, };

class CRecordHandler
{
public:

	CRecordHandler();
	~CRecordHandler();

	static CRecordHandler& Inst();

	void start();
	void stop();
	void pause();
	void resume();
	void SetVolume(bool mute = false);
	void SetMicro(bool mute = false);
	void SetArea(const POINT& p, const SIZE& s);
	void SetMainWindows(const HWND& hwnd);

protected:

	void init();
	void uninit();

	std::string GenerateFileName();
private:
	CRecordHandler(CRecordHandler&);
	CRecordHandler operator= (const CRecordHandler&);

	bool MuteVolume;
	bool MuteMicroPhone;
	bool recording;
	std::string file;
	POINT _p;
	SIZE _s;
	HWND _hwnd;
	size_t count;
	bool _inited;
};

