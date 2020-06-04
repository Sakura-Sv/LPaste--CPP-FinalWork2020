//
// Created by 刘镇 on 2020/6/4.
//

#ifndef C__FINALWORK_LOWLEVELKEYBOARDHOOK_H
#define C__FINALWORK_LOWLEVELKEYBOARDHOOK_H

#include <windef.h>
#include <QtCore/QtGlobal>
#include <winuser.h>
#include <functional>

class LowLevelKeyboardHook
{
public:
    LowLevelKeyboardHook();
    ~LowLevelKeyboardHook();

public:
    static LRESULT CALLBACK keyHookEvent(int nCode, WPARAM wParam, LPARAM lParam);

    void setKeyboardCall(const std::function<void ()> & callBackFunc){ this->callBackFunc = callBackFunc; }

private:
    static HHOOK keyboardHook;
    static std::function<void()> callBackFunc;
};

LowLevelKeyboardHook::LowLevelKeyboardHook()
{
    Q_ASSERT(!keyboardHook);
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)keyHookEvent, GetModuleHandle(NULL), 0);
}

LowLevelKeyboardHook::~LowLevelKeyboardHook()
{
    if (nullptr != keyboardHook) {
        UnhookWindowsHookEx(keyboardHook);
        keyboardHook = nullptr;
    }
}

LRESULT CALLBACK LowLevelKeyboardHook::keyHookEvent(int code, WPARAM wParam, LPARAM lParam)
{
    if (code < 0)
        return CallNextHookEx(keyboardHook, code, wParam, lParam);
    if (wParam == WM_KEYDOWN)
    {
        if (((KBDLLHOOKSTRUCT *)lParam)->vkCode == VK_F1)
        {
            if (callBackFunc)
            {
                callBackFunc();
            }
        }
    }
    return CallNextHookEx(keyboardHook, code, wParam, lParam);
}

#endif //C__FINALWORK_LOWLEVELKEYBOARDHOOK_H
