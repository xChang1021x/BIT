#include <windows.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <Tlhelp32.h>
#include <stdio.h>
#include <tchar.h>
#include <shlwapi.h>
#include <psapi.h>

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib,"kernel32.lib")

using namespace std;

// 显示内存块的保护状态
void printProtection(DWORD dwTarget)
{
	char as[] = "----------";
	if (dwTarget & PAGE_NOACCESS) as[0] = 'N';
	if (dwTarget & PAGE_READONLY) as[1] = 'R';
	if (dwTarget & PAGE_READWRITE) as[2] = 'W';
	if (dwTarget & PAGE_WRITECOPY) as[3] = 'C';
	if (dwTarget & PAGE_EXECUTE) as[4] = 'X';
	if (dwTarget & PAGE_EXECUTE_READ) as[5] = 'r';
	if (dwTarget & PAGE_EXECUTE_READWRITE) as[6] = 'w';
	if (dwTarget & PAGE_EXECUTE_WRITECOPY) as[7] = 'c';
	if (dwTarget & PAGE_GUARD) as[8] = 'G';
	if (dwTarget & PAGE_NOCACHE) as[9] = 'D';
	if (dwTarget & PAGE_WRITECOMBINE) as[10] = 'B';
	printf("  %s  ", as);
}

// 显示系统内存配置信息
void displaySystemConfig()
{
	SYSTEM_INFO si;
	memset(&si, 0, sizeof(si));
	GetNativeSystemInfo(&si);

	TCHAR str_page_size[MAX_PATH];
	StrFormatByteSize(si.dwPageSize, str_page_size, MAX_PATH);

	DWORD memory_size = (DWORD)si.lpMaximumApplicationAddress - (DWORD)si.lpMinimumApplicationAddress;
	TCHAR str_memory_size[MAX_PATH];
	StrFormatByteSize(memory_size, str_memory_size, MAX_PATH);

	printf("获取系统信息\n");
	cout << "--------------------------------------------" << endl;
	cout << "处理器架构               | " << (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 || si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL ? "x64" : "x86") << endl;
	cout << "处理器核心数             | " << si.dwNumberOfProcessors << endl;
	cout << "虚拟内存页大小           | " << str_page_size << endl;
	cout << "最小应用程序地址         | 0x" << hex << setfill('0') << setw(8) << (DWORD)si.lpMinimumApplicationAddress << endl;
	cout << "最大应用程序地址         | 0x" << hex << setw(8) << (DWORD)si.lpMaximumApplicationAddress << endl;
	cout << "可用虚拟内存总量         | " << str_memory_size << endl;
	cout << "--------------------------------------------" << endl;
}

// 显示内存使用情况
void displayMemoryCondition()
{
	printf("获取内存状态\n");
	cout << "--------------------------------------------" << endl;
	MEMORYSTATUSEX stat;
	stat.dwLength = sizeof(stat);
	GlobalMemoryStatusEx(&stat);

	long int DIV = 1024 * 1024;
	cout << "内存使用率              | " << setbase(10) << stat.dwMemoryLoad << "%\n"
		<< "物理内存总量            | " << stat.ullTotalPhys / DIV << "MB\n"
		<< "可用物理内存            | " << stat.ullAvailPhys / DIV << "MB\n"
		<< "分页文件总量            | " << stat.ullTotalPageFile / DIV << "MB\n"
		<< "可用分页文件            | " << stat.ullAvailPageFile / DIV << "MB\n"
		<< "虚拟内存总量            | " << stat.ullTotalVirtual / DIV << "MB\n"
		<< "可用虚拟内存            | " << stat.ullAvailVirtual / DIV << "MB" << endl;
	cout << "--------------------------------------------" << endl;
}

// 显示进程列表
void getAllProcessInformation()
{
	printf("获取进程快照\n");

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);
	HANDLE hProcessShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessShot == INVALID_HANDLE_VALUE)
	{
		printf("无法创建进程快照。\n");
		return;
	}

	cout << " |  序号  |  PID   |  进程名称" << endl;
	cout << "-----------------------------------------" << endl;
	if (Process32First(hProcessShot, &pe32)) {
		for (int i = 0; Process32Next(hProcessShot, &pe32); i++) {
			wprintf(L" | %4d  | %5d  |  %s\n", i, pe32.th32ProcessID, pe32.szExeFile);
		}
	}
	cout << "-----------------------------------------" << endl;
	CloseHandle(hProcessShot);
}

// 显示帮助信息
void ShowHelp()
{
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "输入以下命令: " << endl
		<< "\"config\"   : 显示系统内存配置信息。" << endl
		<< "\"condition\": 显示系统内存使用情况。" << endl
		<< "\"process\"  : 显示所有正在运行的进程信息（包括PID）。" << endl
		<< "\"pid\"      : 输入进程PID，显示详细信息。" << endl
		<< "\"help\"     : 显示此帮助文本。" << endl
		<< "\"exit\"     : 退出程序。" << endl;
	cout << "--------------------------------------------------------------------------" << endl;
}

// 显示特定进程的内存分配情况
void getProcessDetail(int pid)
{
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
	if (!hProcess) return;

	cout << " | 内存地址    | 大小    | 页状态    | 保护状态    | 类型  | 模块名称" << endl;

	SYSTEM_INFO si;
	ZeroMemory(&si, sizeof(si));
	GetSystemInfo(&si);

	MEMORY_BASIC_INFORMATION mbi;
	ZeroMemory(&mbi, sizeof(mbi));
	LPCVOID pBlock = (LPVOID)si.lpMinimumApplicationAddress;

	while (pBlock < si.lpMaximumApplicationAddress) {
		if (VirtualQueryEx(hProcess, pBlock, &mbi, sizeof(mbi)) == sizeof(mbi))
		{
			LPCVOID pEnd = (PBYTE)pBlock + mbi.RegionSize;
			TCHAR szSize[MAX_PATH];
			StrFormatByteSize(mbi.RegionSize, szSize, MAX_PATH);

			cout.fill('0');
			cout << hex << setw(8) << (DWORD)pBlock << "-"
				<< hex << setw(8) << (DWORD)pEnd - 1 << " | ";
			printf("%10ls", szSize);

			switch (mbi.State) {
			case MEM_COMMIT: cout << " | 已提交 | "; break;
			case MEM_FREE: cout << " | 空闲   | "; break;
			case MEM_RESERVE: cout << " | 保留   | "; break;
			default: cout << "          | "; break;
			}

			printProtection(mbi.Protect);

			switch (mbi.Type) {
			case MEM_IMAGE: cout << " | 图像  | "; break;
			case MEM_PRIVATE: cout << " | 私有  | "; break;
			case MEM_MAPPED: cout << " | 映射  | "; break;
			default: cout << " |       | "; break;
			}

			TCHAR str_module_name[MAX_PATH];
			if (GetModuleFileName((HMODULE)pBlock, str_module_name, MAX_PATH) > 0) {
				PathStripPath(str_module_name);
				wprintf(L"%s", str_module_name);
			}
			cout << endl;
			pBlock = pEnd;
		}
	}
}

int main()
{

	cout << "*----------- 系统内存管理器 -----------*" << endl;
	cout << "-- 输入 'help' 查看帮助。" << endl;

	string cmd;
	char cmd_charstr[127];

	while (1)
	{
		cout << "Manager> ";
		cin.getline(cmd_charstr, 127);
		cmd = cmd_charstr;

		if (cmd == "config") displaySystemConfig();
		else if (cmd == "condition") displayMemoryCondition();
		else if (cmd == "process") getAllProcessInformation();
		else if (cmd == "pid") {
			int pid; cout << "输入PID> "; cin >> pid; cin.ignore();
			if (pid > 0) getProcessDetail(pid);
		}
		else if (cmd == "help") ShowHelp();
		else if (cmd == "exit") break;
		else cout << "无效命令，请输入 \"help\" 查看帮助。" << endl;
	}

	return 0;
}
