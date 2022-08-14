#include <Windows.h>
#include <stdio.h>

int main()
{
    HKEY hKey;
    DWORD dwDisposition;
    LONG result;

    result = RegCreateKeyEx(
        // HKEY_LOCAL_MACHINE,
        // "SYSTEM\\CurrentControlSet\\Control\\Keyboard Layout",
        HKEY_CURRENT_USER,
        "Keyboard Layout",
        0, NULL,
        //REG_OPTION_NON_VOLATILE, // 不揮発性
        REG_OPTION_VOLATILE, // 揮発性 (再起動で消える)
        KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition);
    printf("Open: %s\n", result == ERROR_SUCCESS ? "OK" : "NG");

    unsigned char aData[0x15] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x02, 0x00, 0x00, 0x00,
        0x0F, 0x00, 0x45, 0x00,
        0x00, 0x00, 0x00, 0x00,
    };

    result = RegSetValueEx(hKey, "Scancode Map", 0, REG_BINARY, aData, sizeof(aData));
    printf("Write: %s\n", result == ERROR_SUCCESS ? "OK" : "NG");

    RegCloseKey(hKey);

    return 0;
}
