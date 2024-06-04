#include "Byond.h"
#include "Helper.h"

ByondDungClient__Ctor ByondIntegration::CreateDungClientFunc = NULL;
ByondServerPort ByondIntegration::GetServerPortFunc = NULL;
ByondServerIp ByondIntegration::GetServerIpFunc = NULL;

void* ByondIntegration::DungClient;
int ByondIntegration::Major = 0;
int ByondIntegration::Minor = 0;

void ByondIntegration::LoadByondFunctions()
{
	CreateDungClientFunc = (ByondDungClient__Ctor)GetProcAddress(GetModuleHandleA("byondcore.dll"), "??0DungClient@@QAE@XZ");
	GetServerPortFunc = (ByondServerPort)GetProcAddress(GetModuleHandleA("byondcore.dll"), "?GetRemoteServerPort@DungClient@@QAEKXZ_0");
	GetServerIpFunc = (ByondServerIp)GetProcAddress(GetModuleHandleA("byondcore.dll"), "?GetServerIP@DungClient@@QAEPBDPBD@Z");

	ByondVersion gbv = (ByondVersion)GetProcAddress(GetModuleHandleA("byondcore.dll"), "?GetByondVersion@ByondLib@@QAEJXZ");
	ByondBuild gbb = (ByondBuild)GetProcAddress(GetModuleHandleA("byondcore.dll"), "?GetByondBuild@ByondLib@@QAEJXZ");
	if (gbb && gbv) {
		Major = gbv();
		Minor = gbb();
	}
}

void ByondIntegration::LoadDungClient(HMODULE byondcoreModule)
{
	char* dungclient = (char*)AOBScan(byondcoreModule, "55 8B EC 6A FF 68 8F B2");
	std::stringstream ss;
	ss << std::hex << (int)dungclient;
	Log("[LoadDungClient] DungClient: 0x" + ss.str());

	ByondIntegration::DungClient = dungclient;
}

void* __fastcall ByondIntegration::CreateDungClient(void* pThis)
{
	ByondIntegration::DungClient = pThis;
	return ByondIntegration::CreateDungClientFunc(pThis);
}

int __declspec(dllexport) ByondIntegration::GetByondMajorVersion()
{
	return Major;
}

int __declspec(dllexport) ByondIntegration::GetByondMinorVersion()
{
	return Minor;
}

std::string __declspec(dllexport) ByondIntegration::GetByondVersion()
{
	return std::to_string(Major) + "." + std::to_string(Minor);
}

std::string __declspec(dllexport) ByondIntegration::GetServerIp()
{
	if (!DungClient) {
		Log("[ServerIP] DungClient is null");
		return std::string();
	}

	char serverIp[256];
	return std::string(GetServerIpFunc(DungClient, 0, serverIp));
}
