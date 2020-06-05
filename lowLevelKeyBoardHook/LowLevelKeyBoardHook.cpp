//
// Created by 刘镇 on 2020/6/4.
//

#include "LowLevelKeyBoardHook.h"

HHOOK LowLevelKeyboardHook::keyboardHook = nullptr;
std::function<void(int)> LowLevelKeyboardHook::callBackFunc = nullptr;

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
                callBackFunc((int)VK_F1);
            }
        }
        if (((KBDLLHOOKSTRUCT *)lParam)->vkCode == VK_F3)
        {
            if (callBackFunc)
            {
                callBackFunc((int)VK_F3);
            }
        }
    }
    return CallNextHookEx(keyboardHook, code, wParam, lParam);
}