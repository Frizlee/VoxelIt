#include <iostream>
#include <vector>
#include <string>
#include "Application.hpp"
using namespace std;

int main(int argc, char **argv)
{
    try
    {
        Application app;
        vector<string> args;
        args.assign(argv, argv + argc);
        app.setArgs(args);
        app.run();
    }
    catch (runtime_error err)
    {
        cerr << err.what() << endl;
    }
    return 0;
}