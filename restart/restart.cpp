#include <iostream>
#include <Windows.h>

int main() {
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        std::cerr << "OpenProcessToken failed, error " << GetLastError() << std::endl;
        return 1;
    }
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
    if (GetLastError() != ERROR_SUCCESS) {
        std::cerr << "AdjustTokenPrivileges failed, error " << GetLastError() << std::endl;
        return 1;
    
    // Faire Crash le Systeme
    if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCEIFHUNG, SHTDN_REASON_MAJOR_OTHER | SHTDN_REASON_MINOR_OTHER)) {
        std::cerr << "ExitWindowsEx failed, error " << GetLastError() << std::endl;
        return 1;
    }

    return 0;
}
