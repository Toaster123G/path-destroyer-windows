#include <iostream>
#include <string>
// windows api
#include <Windows.h>
// OS processes list
#include <TlHelp32.h>

int main() {
    std::wstring inData;
    std::wstring delPath;

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // --- Some things about Win API: --- 
    // 1) if we use wcout/wcin - we can use default std out/cin with this windows output commands
    // because it's consists to buffer overflow
    // 2) "L" around text, because windows output needs advanced unicode (Unicode+)
    // which can reading any languages and symbols
    // 3) "\n" after wroten text, because it's helped us to read new clear line.
    // This is mean, console buffer starting from clear line wich can be stored our writed path.

// Use default UTF-8 stroke (char*)
    const char* BANNER = R"(
  ██████╗ ██╗  ██╗██████╗ ██╗████████╗
 ██╔════╝ ██║  ██║██╔══██╗██║╚══██╔══╝
 ███████╗ ███████║██████╔╝██║   ██║   
 ██╔═══██╗╚════██║██╔══██╗██║   ██║   
 ╚██████╔╝     ██║██████╔╝██║   ██║   
  ╚═════╝      ╚═╝╚═════╝ ╚═╝   ╚═╝   

██████╗ ███████╗███████╗████████╗██████╗  ██████╗ ██╗   ██╗███████╗██████╗ 
██╔══██╗██╔════╝██╔════╝╚══██╔══╝██╔══██╗██╔═══██╗╚██╗ ██╔╝██╔════╝██╔══██╗
██║  ██║█████╗  ███████╗   ██║   ██████╔╝██║   ██║ ╚████╔╝ █████╗  ██████╔╝
██║  ██║██╔══╝  ╚════██║   ██║   ██╔══██╗██║   ██║  ╚██╔╝  ██╔══╝  ██╔══██╗
██████╔╝███████╗███████║   ██║   ██║  ██║╚██████╔╝   ██║   ███████╗██║  ██║
╚═════╝ ╚══════╝╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝    ╚═╝   ╚══════╝╚═╝  ╚═╝
)";

    std::wcout << BANNER << L"\n";
    std::wcout << L"Write file/folder path for delete them.\n";
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
        // DeleteFileW don't delete actual data by the path permanently zero out of hard drive
        // the actual data space marked like UNALLOCATED SPACE and that's why we can't seeing deleted data in the bucket
        // any action (created file/folder, installing something) will be taking this UNALLOCATED SPACE to new data
        // -----------------------------------------------------
       
        // Giving structure to SHFileOperationW
            std::wstring doubleNullPath = inData + L'\0'; 
            
            // SHFileOperationW structure set up
            SHFILEOPSTRUCTW fileOp = { 0 };
            fileOp.wFunc = FO_DELETE;
            fileOp.pFrom = doubleNullPath.c_str();
            fileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI;
        
            // change old delete-info logic + checking initial SHFileOperationW structure
            if (SHFileOperationW(&fileOp) == 0) {
                std::wcout << L"Deleted complete!\n\n";
            } else {
                std::wcout << L"Delete error occurred.\n\n";
            }

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