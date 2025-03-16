#pragma once

typedef struct 
{
	unsigned long Offset;
	unsigned char Bytes[32];

}Database;

extern HINSTANCE    DllInstance;
extern HHOOK        m_Keyboard;
extern HANDLE       Thread;
extern DWORD WINAPI MainThread(LPVOID lpParam);

//void SplashShow();
void Initialize();
bool ScanDump();
void HiddenScan();
void ClasseCheckWindow();
void ClasseWindow(LPCSTR WindowClasse);