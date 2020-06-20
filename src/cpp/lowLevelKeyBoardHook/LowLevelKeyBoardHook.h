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

    void setKeyboardCall(const std::function<void(int)> & callBackFunc){ this->callBackFunc = callBackFunc; }

private:
    static HHOOK keyboardHook;
    static std::function<void(int)> callBackFunc;
};

#endif //C__FINALWORK_LOWLEVELKEYBOARDHOOK_H
