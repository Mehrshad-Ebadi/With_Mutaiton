#include <iostream>
#include <cstdlib>  // For the system() function

using namespace std;

int main() {
    // Source and destination paths
    string sourcePath = "./boz.txt";
    string destPath = "./khar.txt";

    // Construct the cp command
    string command = "cp " + sourcePath + " " + destPath;

    // Execute the cp command
    int result = system(command.c_str());

    if (result == 0) {
        cout << "File copied successfully!" << endl;
    } else {
        cerr << "Failed to copy file." << endl;
    }

    return 0;
}