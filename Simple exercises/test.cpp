#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

int main() {
    // Execute the git command
    string command = "git rev-list --all --count";
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        cerr << "Error: Could not open pipe for git command." << endl;
        return 1;
    }

    // Read the output from the pipe
    char buffer[128];
    string result;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        result += buffer;
    }

    // Close the pipe
    pclose(pipe);

    // Remove trailing newline if present
    if (!result.empty() && result[result.size() - 1] == '\n') {
        result.erase(result.size() - 1);
    }

    // Convert the string to an integer
    int git_count = stoi(result);

    // Calculate major, minor, and patch versions
    int patch = git_count % 9;
    int minor = git_count / 9;
    int major = minor / 9;

    // Print the version string
    cout << "v" << major << "." << minor << "." << patch << endl;

    return 0;
}