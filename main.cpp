#include <iostream>
#include <string>
// windows global lib
#include <Windows.h>
// processers list on the system
#include <TlHelp32.h>

int main() {
    std::wstring inData;
    std::wstring delPath;

    std::wcout << L"[ UTIL LOAD ]\n";
    std::wcout << L"Write file/folder path for delete them.\n";
    std::wcout << L"Example:\n";
    // std::wcout << L"c:/users/dima/desktop/CPU-schema.pdf\n\n";
    std::wcout << L"Path: ";

    std::getline(std::wcin, inData);

    // change input type to wide-stroke type
    // DeleteFileW get only wide-stroke type (multi UNICODE type)
    LPCWSTR processPath = inData.c_str();

    DWORD writedPath = GetFileAttributesW(processPath);

    // check correct writed file path with ternary operators
    bool pathChecker = (writedPath != INVALID_FILE_ATTRIBUTES) ? true : false;
    // without "()" algorithm will be incorrect (lower precedence)
    std::wcout << (pathChecker ? L"File is exist\n\n" : L"File does not exist\n\n");

    if (pathChecker == true){
        std::wcout << L"Delete [" << inData << L"]?\n";
        std::wcout << L"Y (yes) / N (no)\n\n";
        std::getline(std::wcin, delPath);  

        if (delPath == L"Y" || delPath == L"y"){
        // use absolute delete func from windows API, it's delete files or folders from memory
        // and that means one - you don't see deleted data at the bucket!
        DeleteFileW(processPath);
        std::wcout << L"Deleted complete!\n\n";
        } else if (delPath == L"N" || delPath == L"n"){
            std::wcout << L"Delete canceled.\n\n";
        } else {
            DWORD error = GetLastError();
            std::wcout << L"Error: " << error << L"\n\n";

        }
    } else{
        DWORD error = GetLastError();
        std::wcout << L"Path error: " << error << L"\n\n";
    }
    
    

    return 0;
}