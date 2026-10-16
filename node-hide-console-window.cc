#include <node.h>
#ifdef _WIN32
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
#else
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>

static Window FindWindowByPid(Display *display, Window window, Atom pidAtom, pid_t targetPid)
{
    Atom actualType;
    int actualFormat;
    unsigned long nItems, bytesAfter;
    unsigned char *prop = NULL;

    if (XGetWindowProperty(display, window, pidAtom, 0, 1, False, XA_CARDINAL,
                           &actualType, &actualFormat, &nItems, &bytesAfter, &prop) == Success)
    {
        if (prop && nItems == 1)
        {
            pid_t windowPid = *(pid_t *)prop;
            XFree(prop);
            if (windowPid == targetPid)
                return window;
        }
        else if (prop)
        {
            XFree(prop);
        }
    }

    Window root, parent;
    Window *children = NULL;
    unsigned int nChildren = 0;

    if (XQueryTree(display, window, &root, &parent, &children, &nChildren))
    {
        for (unsigned int i = 0; i < nChildren; ++i)
        {
            Window found = FindWindowByPid(display, children[i], pidAtom, targetPid);
            if (found != None)
            {
                if (children)
                    XFree(children);
                return found;
            }
        }
        if (children)
            XFree(children);
    }

    return None;
}

static pid_t GetTerminalPid()
{
    pid_t pid = getpid();
    char path[64];
    char buf[256];
    while (pid > 1)
    {
        snprintf(path, sizeof(path), "/proc/%d/stat", pid);
        FILE *f = fopen(path, "r");
        if (!f)
            break;
        int p;
        char state;
        pid_t ppid;
        if (fscanf(f, "%d %*s %c %d", &p, &state, &ppid) != 3)
        {
            fclose(f);
            break;
        }
        fclose(f);
        snprintf(path, sizeof(path), "/proc/%d/comm", pid);
        f = fopen(path, "r");
        if (f)
        {
            if (fgets(buf, sizeof(buf), f))
            {
                size_t len = strlen(buf);
                if (len > 0 && buf[len - 1] == '\n')
                    buf[len - 1] = 0;
                if (strstr(buf, "gnome-terminal") || strstr(buf, "konsole") ||
                    strstr(buf, "xterm") || strstr(buf, "kitty") ||
                    strstr(buf, "alacritty") || strstr(buf, "terminator") ||
                    strstr(buf, "xfce4-terminal") || strstr(buf, "mate-terminal") ||
                    strstr(buf, "lxterminal") || strstr(buf, "tilix") ||
                    strstr(buf, "termite") || strstr(buf, "urxvt") ||
                    strstr(buf, "rxvt") || strstr(buf, "st") ||
                    strstr(buf, "wezterm") || strstr(buf, "foot") ||
                    strstr(buf, "hyper") || strstr(buf, "terminal") ||
                    strstr(buf, "yakuake") || strstr(buf, "guake") ||
                    strstr(buf, "tilda") || strstr(buf, "sakura") ||
                    strstr(buf, "roxterm") || strstr(buf, "qterminal") ||
                    strstr(buf, "deepin-terminal") || strstr(buf, "cool-retro-term") ||
                    strstr(buf, "terminology") || strstr(buf, "pantheon-terminal") ||
                    strstr(buf, "io.elementary.terminal") || strstr(buf, "kgx") ||
                    strstr(buf, "blackbox") || strstr(buf, "contour") ||
                    strstr(buf, "tabby") || strstr(buf, "wave") ||
                    strstr(buf, "ghostty") || strstr(buf, "rio") ||
                    strstr(buf, "warp") || strstr(buf, "zutty") ||
                    strstr(buf, "mlterm") || strstr(buf, "Eterm") ||
                    strstr(buf, "aterm") || strstr(buf, "mrxvt") ||
                    strstr(buf, "pterm") || strstr(buf, "lxterm") ||
                    strstr(buf, "x-terminal-emulator"))
                {
                    fclose(f);
                    return pid;
                }
            }
            fclose(f);
        }
        pid = ppid;
    }
    return getppid();
}

static Window GetTargetWindow()
{
    Display *display = XOpenDisplay(NULL);
    if (!display)
        return None;

    Atom pidAtom = XInternAtom(display, "_NET_WM_PID", True);
    if (pidAtom == None)
    {
        XCloseDisplay(display);
        return None;
    }

    pid_t targetPid = GetTerminalPid();
    Window root = DefaultRootWindow(display);
    Window found = FindWindowByPid(display, root, pidAtom, targetPid);

    if (found == None)
    {
        targetPid = getppid();
        found = FindWindowByPid(display, root, pidAtom, targetPid);
    }

    if (found == None)
    {
        targetPid = getpid();
        found = FindWindowByPid(display, root, pidAtom, targetPid);
    }

    XCloseDisplay(display);
    return found;
}

void HideConsole(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    Display *display = XOpenDisplay(NULL);
    if (!display)
        return;

    Window window = GetTargetWindow();
    if (window != None)
    {
        XUnmapWindow(display, window);
        XFlush(display);
    }

    XCloseDisplay(display);
}

void ShowConsole(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    Display *display = XOpenDisplay(NULL);
    if (!display)
        return;

    Window window = GetTargetWindow();
    if (window != None)
    {
        XMapWindow(display, window);
        XRaiseWindow(display, window);
        XFlush(display);
    }

    XCloseDisplay(display);
}
#endif

void Initialize(v8::Local<v8::Object> exports) {
    NODE_SET_METHOD(exports, "hideConsole", HideConsole);
    NODE_SET_METHOD(exports, "showConsole", ShowConsole);
}

NODE_MODULE(addon, Initialize);
