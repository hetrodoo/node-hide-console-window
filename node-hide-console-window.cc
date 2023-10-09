#include <node.h>
#include <Windows.h>

HWND GetTargetWindow()
{
    HWND consoleWindow = GetConsoleWindow();
    HWND parentWindow = GetParent(consoleWindow);

    if (parentWindow == NULL)
    {
        return consoleWindow;
    }

    return parentWindow;
}

void HideConsole(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    ShowWindow(GetTargetWindow(), SW_HIDE);
}

void ShowConsole(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    ShowWindow(GetTargetWindow(), SW_SHOW);
}

void Initialize(v8::Local<v8::Object> exports) {
    NODE_SET_METHOD(exports, "hideConsole", HideConsole);
    NODE_SET_METHOD(exports, "showConsole", ShowConsole);
}

NODE_MODULE(addon, Initialize);
