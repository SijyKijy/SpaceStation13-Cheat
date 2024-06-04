#pragma once
#include <Windows.h>
#include "Utils.cpp"

typedef void* (__thiscall* ByondDungClient__Ctor)(void* pThis);
typedef unsigned int(__fastcall* ByondServerPort)(void* dungClient);
typedef char* (__fastcall* ByondServerIp)(void* dungClient, void*, char* str);
typedef int (*ByondVersion)();
typedef int (*ByondBuild)();

namespace ByondIntegration {
	extern void* DungClient;

	extern ByondDungClient__Ctor CreateDungClientFunc;
	extern ByondServerPort GetServerPortFunc;
	extern ByondServerIp GetServerIpFunc;

	extern int Major;
	extern int Minor;

	void LoadByondFunctions();
	void LoadDungClient(HMODULE byondcoreModule);

	void* __fastcall CreateDungClient(void* pThis);

	int __declspec(dllexport) GetByondMajorVersion();
	int __declspec(dllexport) GetByondMinorVersion();
	std::string __declspec(dllexport) GetByondVersion();
	std::string __declspec(dllexport) GetServerIp();
}