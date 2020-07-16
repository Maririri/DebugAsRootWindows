#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <Windows.h>

BOOL IsProcessElevated() {
    BOOL fIsElevated = FALSE;
    HANDLE hToken = NULL;
    TOKEN_ELEVATION elevation;
    DWORD dwSize;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
        printf("\n Failed to get Process Token :%d.", GetLastError());
        goto Cleanup;  // if Failed, we treat as False
    }

    if (!GetTokenInformation(hToken, TokenElevation, &elevation, sizeof(elevation), &dwSize)) {
        printf("\nFailed to get Token Information :%d.", GetLastError());
        goto Cleanup;// if Failed, we treat as False
    }

    fIsElevated = elevation.TokenIsElevated;

    Cleanup:
    if (hToken) {
        CloseHandle(hToken);
        hToken = NULL;
    }
    return fIsElevated;
}

int main(int argc, char *argv[]) {
    char *user = getenv("USER");
    char *path = getenv("Path");
    char *java_home = getenv("JAVA_HOME");
    char *tmp = getenv("TMP");
    if (user != nullptr) {
        printf("USER='%s'\n", user);
        printf("Path='%s'\n", path);
        printf("JAVA_HOME='%s'\n", java_home);
        printf("TMP='%s'\n", tmp);
    }

    std::cout << "IsProcessElevated: " << (IsProcessElevated() ? "yes" : "no") << std::endl;

    return 0;
}