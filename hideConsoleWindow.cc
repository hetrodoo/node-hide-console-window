#include <node.h>
#include <iostream>
#include <Windows.h>
using namespace std;

void HideConsole(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void ShowConsole(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

void Initialize(v8::Local<v8::Object> exports) {
    NODE_SET_METHOD(exports, "HideConsole", HideConsole);
    NODE_SET_METHOD(exports, "ShowConsole", ShowConsole);
}

NODE_MODULE(addon, Initialize);