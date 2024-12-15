SetBatchLines -1
ListLines Off
Process, Priority,, H
Lastexe :=0
#KeyHistory 0
#UseHook
#InstallKeybdHook
#InstallMouseHook
#NoEnv
#SingleInstance Force
#include AHKHID.ahk

timeout:=0, start:=0

PowrProfModule:=DllCall("LoadLibrary", "Str", "powrprof.dll", "Ptr")

RunWait, %A_ComSpec% /c powercfg /aliasesh > "%A_Temp%\%A_ScriptName%.txt",, hide
Loop, Read, %A_Temp%\%A_ScriptName%.txt
{
   if start and InStr(A_LoopReadLine, "SUB_")
       break

   if InStr(A_LoopReadLine, "SUB_PROCESSOR")
       start:=A_Index

   if (start)
   {
       line:=StrReplace(A_LoopReadLine, A_Space A_Space A_Space A_Space, A_Space)
       line:=StrReplace(line, A_Space A_Space, A_Space)
       alias:=SubStr(line, 38)
       GUID:=SubStr(line, 1, 36)

       VarSetCapacity(%alias%, 16)
       DllCall("ole32.dll\CLSIDFromString", "WStr", "{" GUID "}", "Ptr", &%alias%)
   }
}
FileDelete, %A_Temp%\%A_ScriptName%.txt
line:="", alias:="", GUID:=""

RegRead, OutputVar, HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Power\User\PowerSchemes, ActivePowerScheme
VarSetCapacity(scheme_current, 16)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{" OutputVar "}", "Ptr", &scheme_current)

AHKHID_Register(13, 5, A_ScriptHwnd, RIDEV_INPUTSINK)
OnMessage(0xFF, "InputMsg")

DllCall("RegisterShellHookWindow", "Ptr", A_ScriptHwnd)
OnMessage(DllCall("RegisterWindowMessage", "Str", "SHELLHOOK"), "ShellMessage")

OnExit, ExitSub
Return

ExitSub:
   AHKHID_Register(13, 5, 0, RIDEV_REMOVE)
   DllCall("DeregisterShellHookWindow", "Ptr", A_ScriptHwnd)
   DllCall("FreeLibrary", "Ptr", PowrProfModule)
   Boost()
ExitApp

~^s::
   if InStr(title, A_ScriptName)
       Reload
Return

~*LButton::
~*RButton::
~*MButton::
~*Home::
~*End::
~*PgUp::
~*PgDn::
~*Up::
~*Down::
~*Left::
~*Right::
~*Esc::
~*Tab::
~LWin::
~*Enter::
~*Space::
~*Backspace::
~*Delete::
~*Insert::
~*F1::
~*F2::
~*F3::
~*F4::
~*F5::
~*F6::
~*F7::
~*F8::
~*F9::
~*F10::
~*F11::
~*F12::
~+^#F22::
~+^#F24::
~*a::
~*b::
~*c::
~*d::
~*e::
~*f::
~*g::
~*h::
~*i::
~*j::
~*k::
~*l::
~*m::
~*n::
~*o::
~*p::
~*q::
~*r::
~*s::
~*t::
~*u::
~*v::
~*w::
~*x::
~*y::
~*z::
~*1::
~*2::
~*3::
~*4::
~*5::
~*6::
~*7::
~*8::
~*9::
~*0::
~*/::
~*\::
~*,::
~*.::
~*;::
~*'::
~*[::
~*]::
~*-::
~*=::
~*`::
   Boost(1)
Return

InputMsg(wParam, lParam) {
   AHKHID_GetInputData(lParam, uData)
   if NumGet(uData, 8, "UChar")=2
       Boost(2)
   Return 0
}

ShellMessage(wParam, lParam) {
   Boost(1)
   Return 0
}

ResetDelay() {
   global
   if (timeout=2)
   {
       AHKHID_Register(13, 5, A_ScriptHwnd, RIDEV_INPUTSINK)
       SetTimer, Boost, -500
   }
   else if GetKeyState("LButton", "P")
       Boost(1)
   else Boost(2)
}

Boost(set:=0) {
   global
   SetTimer, Boost, Off
   SetTimer, ResetDelay, Off
   if (set)
       AHKHID_Register(13, 5, 0, RIDEV_REMOVE)

   if (timeout!=set)
   {
       WinGet, exe, ProcessName, A
       WinGetTitle, title, A
       timeout:=set
       switch
        {
        case exe="code.exe":
            if(Lastexe!="code.exe"){
                DllCall("powrprof.dll\PowerWriteDCValueIndex", "Ptr", 0, "Ptr", &scheme_current, "Ptr", &sub_processor, "Ptr", &procthrottlemax, "UInt", 67)
                DllCall("powrprof.dll\PowerWriteDCValueIndex", "Ptr", 0, "Ptr", &scheme_current, "Ptr", &sub_processor, "Ptr", &procthrottlemin, "UInt", 5)
                DllCall("powrprof.dll\PowerWriteDCValueIndex", "Ptr", 0, "Ptr", &scheme_current, "Ptr", &sub_processor, "Ptr", &cpmincores, "UInt", 20)
                 DllCall("powrprof.dll\PowerWriteDCValueIndex", "Ptr", 0, "Ptr", &scheme_current, "Ptr", &sub_processor, "Ptr", &cpmaxcores, "UInt", 20)
                }
                else return;
        case timeout=1:
            DllCall("powrprof.dll\PowerWriteDCValueIndex", "Ptr", 0, "Ptr", &scheme_current, "Ptr", &sub_processor, "Ptr", &procthrottlemax, "UInt", 67)
            DllCall("powrprof.dll\PowerWriteDCValueIndex", "Ptr", 0, "Ptr", &scheme_current, "Ptr", &sub_processor, "Ptr", &procthrottlemin, "UInt", 5)
            DllCall("powrprof.dll\PowerWriteDCValueIndex", "Ptr", 0, "Ptr", &scheme_current, "Ptr", &sub_processor, "Ptr", &cpmincores, "UInt", 20)
        case timeout=2:
            DllCall("powrprof.dll\PowerWriteDCValueIndex", "Ptr", 0, "Ptr", &scheme_current, "Ptr", &sub_processor, "Ptr", &procthrottlemax, "UInt", 75)
            DllCall("powrprof.dll\PowerWriteDCValueIndex", "Ptr", 0, "Ptr", &scheme_current, "Ptr", &sub_processor, "Ptr", &procthrottlemin, "UInt", 5)
            DllCall("powrprof.dll\PowerWriteDCValueIndex", "Ptr", 0, "Ptr", &scheme_current, "Ptr", &sub_processor, "Ptr", &cpmincores, "UInt", 20)
        case timeout=0:
            DllCall("powrprof.dll\PowerWriteDCValueIndex", "Ptr", 0, "Ptr", &scheme_current, "Ptr", &sub_processor, "Ptr", &procthrottlemax, "UInt", 34)
            DllCall("powrprof.dll\PowerWriteDCValueIndex", "Ptr", 0, "Ptr", &scheme_current, "Ptr", &sub_processor, "Ptr", &procthrottlemin, "UInt", 0)
            DllCall("powrprof.dll\PowerWriteDCValueIndex", "Ptr", 0, "Ptr", &scheme_current, "Ptr", &sub_processor, "Ptr", &cpmincores, "UInt", 5)
        }
        Lastexe:=exe
       DllCall("powrprof.dll\PowerSetActiveScheme", "Ptr", 0, "Ptr", &scheme_current)
   }
   if (timeout)
       SetTimer, ResetDelay, -500
}