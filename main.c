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

    // キー割り当て (変更前 2byte 変更後 2byte のリトルエンディアン)
    // 0x00010002(0x0001 キーに 0x0002 キーを割り当てる)の場合 
    // リトルエンディアン 0x20001000 を書き込む (0x20, 0x00, 0x10, 0x00)
    unsigned char aData[] = {
        0x00, 0x00, 0x00, 0x00, // バージョン (すべて 0)
        0x00, 0x00, 0x00, 0x00, // フラグ (すべて 0)
        0x02, 0x00, 0x00, 0x00, // マッピング数 (null 含める)
        0x0F, 0x00, 0x45, 0x00, // キー割り当て
        0x00, 0x00, 0x00, 0x00, // 終端 null (すべて 0)
    };

    result = RegSetValueEx(hKey, "Scancode Map", 0, REG_BINARY, aData, sizeof(aData));
    printf("Write: %s\n", result == ERROR_SUCCESS ? "OK" : "NG");

    RegCloseKey(hKey);

    return 0;
}
