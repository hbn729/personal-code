SetBatchLines, -1
ListLines Off
Process, Priority,, H
#KeyHistory 0
#UseHook
#InstallKeybdHook
#InstallMouseHook
#NoEnv
#SingleInstance Force
#include AHKHID.ahk

global timeout:=0

PowrProfModule:=DllCall("LoadLibrary", "Str", "powrprof.dll", "Ptr")
Ole32Module:=DllCall("LoadLibrary", "Str", "ole32.dll", "Ptr")

VarSetCapacity(sub_processor, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{54533251-82be-4824-96c1-47b60b740d00}", "Ptr", &sub_processor)
VarSetCapacity(complexunparkpolicy, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{b669a5e9-7b1d-4132-baaa-49190abcfeb6}", "Ptr", &complexunparkpolicy)
VarSetCapacity(cpconcurrency, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{2430ab6f-a520-44a2-9601-f7f23b5134b1}", "Ptr", &cpconcurrency)
VarSetCapacity(cpdecreasepol, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{71021b41-c749-4d21-be74-a00f335d582b}", "Ptr", &cpdecreasepol)
VarSetCapacity(cpdecreasetime, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{dfd10d17-d5eb-45dd-877a-9a34ddd15c82}", "Ptr", &cpdecreasetime)
VarSetCapacity(cpdistribution, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{4bdaf4e9-d103-46d7-a5f0-6280121616ef}", "Ptr", &cpdistribution)
VarSetCapacity(cpheadroom, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{f735a673-2066-4f80-a0c5-ddee0cf1bf5d}", "Ptr", &cpheadroom)
VarSetCapacity(cpincreasepol, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{c7be0679-2817-4d69-9d02-519a537ed0c6}", "Ptr", &cpincreasepol)
VarSetCapacity(cpincreasetime, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{2ddd5a84-5a71-437e-912a-db0b8c788732}", "Ptr", &cpincreasetime)
VarSetCapacity(cpmaxcores, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{ea062031-0e34-4ff1-9b6d-eb1059334028}", "Ptr", &cpmaxcores)
VarSetCapacity(cpmaxcores1, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{ea062031-0e34-4ff1-9b6d-eb1059334029}", "Ptr", &cpmaxcores1)
VarSetCapacity(cpmincores, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{0cc5b647-c1df-4637-891a-dec35c318583}", "Ptr", &cpmincores)
VarSetCapacity(cpmincores1, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{0cc5b647-c1df-4637-891a-dec35c318584}", "Ptr", &cpmincores1)
VarSetCapacity(cpoverutil, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{943c8cb6-6f93-4227-ad87-e9a3feec08d1}", "Ptr", &cpoverutil)
VarSetCapacity(cpperf, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{447235c7-6a8d-4cc0-8e24-9eaf70b96e2b}", "Ptr", &cpperf)
VarSetCapacity(cpperf1, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{447235c7-6a8d-4cc0-8e24-9eaf70b96e2c}", "Ptr", &cpperf1)
VarSetCapacity(distributeutil, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{e0007330-f589-42ed-a401-5ddb10e785d3}", "Ptr", &distributeutil)
VarSetCapacity(heteroclass0floorperf, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{fddc842b-8364-4edc-94cf-c17f60de1c80}", "Ptr", &heteroclass0floorperf)
VarSetCapacity(heteroclass1initialperf, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{1facfc65-a930-4bc5-9f38-504ec097bbc0}", "Ptr", &heteroclass1initialperf)
VarSetCapacity(heterodecreasethreshold, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{f8861c27-95e7-475c-865b-13c0cb3f9d6b}", "Ptr", &heterodecreasethreshold)
VarSetCapacity(heterodecreasethreshold1, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{f8861c27-95e7-475c-865b-13c0cb3f9d6c}", "Ptr", &heterodecreasethreshold1)
VarSetCapacity(heterodecreasetime, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{7f2492b6-60b1-45e5-ae55-773f8cd5caec}", "Ptr", &heterodecreasetime)
VarSetCapacity(heteroincreasethreshold, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{b000397d-9b0b-483d-98c9-692a6060cfbf}", "Ptr", &heteroincreasethreshold)
VarSetCapacity(heteroincreasethreshold1, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{b000397d-9b0b-483d-98c9-692a6060cfc0}", "Ptr", &heteroincreasethreshold1)
VarSetCapacity(heteroincreasetime, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{4009efa7-e72d-4cba-9edf-91084ea8cbc3}", "Ptr", &heteroincreasetime)
VarSetCapacity(heteropolicy, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{7f2f5cfa-f10c-4823-b5e1-e93ae85f46b5}", "Ptr", &heteropolicy)
VarSetCapacity(idlecheck, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{c4581c31-89ab-4597-8e2b-9c9cab440e6b}", "Ptr", &idlecheck)
VarSetCapacity(idledemote, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{4b92d758-5a24-4851-a470-815d78aee119}", "Ptr", &idledemote)
VarSetCapacity(idledisable, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{5d76a2ca-e8c0-402f-a133-2158492d58ad}", "Ptr", &idledisable)
VarSetCapacity(idlepromote, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{7b224883-b3cc-4d79-819f-8374152cbe7c}", "Ptr", &idlepromote)
VarSetCapacity(idlescaling, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{6c2993b0-8f48-481f-bcc6-00dd2742aa06}", "Ptr", &idlescaling)
VarSetCapacity(idlestatemax, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{9943e905-9a30-4ec1-9b99-44dd3b76f7a2}", "Ptr", &idlestatemax)
VarSetCapacity(latencyhintepp, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{4b70f900-cdd9-4e66-aa26-ae8417f98173}", "Ptr", &latencyhintepp)
VarSetCapacity(latencyhintepp1, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{4b70f900-cdd9-4e66-aa26-ae8417f98174}", "Ptr", &latencyhintepp1)
VarSetCapacity(latencyhintperf, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{619b7505-003b-4e82-b7a6-4dd29c300971}", "Ptr", &latencyhintperf)
VarSetCapacity(latencyhintperf1, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{619b7505-003b-4e82-b7a6-4dd29c300972}", "Ptr", &latencyhintperf1)
VarSetCapacity(latencyhintunpark, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{616cdaa5-695e-4545-97ad-97dc2d1bdd88}", "Ptr", &latencyhintunpark)
VarSetCapacity(latencyhintunpark1, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{616cdaa5-695e-4545-97ad-97dc2d1bdd89}", "Ptr", &latencyhintunpark1)
VarSetCapacity(longthreadarchclasslowerthreshold, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{43f278bc-0f8a-46d0-8b31-9a23e615d713}", "Ptr", &longthreadarchclasslowerthreshold)
VarSetCapacity(longthreadarchclassupperthreshold, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{bf903d33-9d24-49d3-a468-e65e0325046a}", "Ptr", &longthreadarchclassupperthreshold)
VarSetCapacity(moduleunparkpolicy, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{b0deaf6b-59c0-4523-8a45-ca7f40244114}", "Ptr", &moduleunparkpolicy)
VarSetCapacity(perfautonomous, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{8baa4a8a-14c6-4451-8e8b-14bdbd197537}", "Ptr", &perfautonomous)
VarSetCapacity(perfautonomouswindow, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{cfeda3d0-7697-4566-a922-a9086cd49dfa}", "Ptr", &perfautonomouswindow)
VarSetCapacity(perfboostmode, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{be337238-0d82-4146-a960-4f3749d470c7}", "Ptr", &perfboostmode)
VarSetCapacity(perfboostpol, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{45bcc044-d885-43e2-8605-ee0ec6e96b59}", "Ptr", &perfboostpol)
VarSetCapacity(perfcheck, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{4d2b0152-7d5c-498b-88e2-34345392a2c5}", "Ptr", &perfcheck)
VarSetCapacity(perfdecpol, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{40fbefc7-2e9d-4d25-a185-0cfd8574bac6}", "Ptr", &perfdecpol)
VarSetCapacity(perfdecpol1, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{40fbefc7-2e9d-4d25-a185-0cfd8574bac7}", "Ptr", &perfdecpol1)
VarSetCapacity(perfdecthreshold, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{12a0ab44-fe28-4fa9-b3bd-4b64f44960a6}", "Ptr", &perfdecthreshold)
VarSetCapacity(perfdecthreshold1, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{12a0ab44-fe28-4fa9-b3bd-4b64f44960a7}", "Ptr", &perfdecthreshold1)
VarSetCapacity(perfdectime, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{d8edeb9b-95cf-4f95-a73c-b061973693c8}", "Ptr", &perfdectime)
VarSetCapacity(perfdectime1, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{d8edeb9b-95cf-4f95-a73c-b061973693c9}", "Ptr", &perfdectime1)
VarSetCapacity(perfdutycycling, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{4e4450b3-6179-4e91-b8f1-5bb9938f81a1}", "Ptr", &perfdutycycling)
VarSetCapacity(perfepp, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{36687f9e-e3a5-4dbf-b1dc-15eb381c6863}", "Ptr", &perfepp)
VarSetCapacity(perfepp1, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{36687f9e-e3a5-4dbf-b1dc-15eb381c6864}", "Ptr", &perfepp1)
VarSetCapacity(perfhistory, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{7d24baa7-0b84-480f-840c-1b0743c00f5f}", "Ptr", &perfhistory)
VarSetCapacity(perfhistory1, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{7d24baa7-0b84-480f-840c-1b0743c00f60}", "Ptr", &perfhistory1)
VarSetCapacity(perfincpol, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{465e1f50-b610-473a-ab58-00d1077dc418}", "Ptr", &perfincpol)
VarSetCapacity(perfincpol1, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{465e1f50-b610-473a-ab58-00d1077dc419}", "Ptr", &perfincpol1)
VarSetCapacity(perfincthreshold, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{06cadf0e-64ed-448a-8927-ce7bf90eb35d}", "Ptr", &perfincthreshold)
VarSetCapacity(perfincthreshold1, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{06cadf0e-64ed-448a-8927-ce7bf90eb35e}", "Ptr", &perfincthreshold1)
VarSetCapacity(perfinctime, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{984cf492-3bed-4488-a8f9-4286c97bf5aa}", "Ptr", &perfinctime)
VarSetCapacity(perfinctime1, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{984cf492-3bed-4488-a8f9-4286c97bf5ab}", "Ptr", &perfinctime1)
VarSetCapacity(procfreqmax, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{75b0ae3f-bce0-45a7-8c89-c9611c25e100}", "Ptr", &procfreqmax)
VarSetCapacity(procfreqmax1, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{75b0ae3f-bce0-45a7-8c89-c9611c25e101}", "Ptr", &procfreqmax1)
VarSetCapacity(procthrottlemax, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{bc5038f7-23e0-4960-96da-33abaf5935ec}", "Ptr", &procthrottlemax)
VarSetCapacity(procthrottlemax1, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{bc5038f7-23e0-4960-96da-33abaf5935ed}", "Ptr", &procthrottlemax1)
VarSetCapacity(procthrottlemin, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{893dee8e-2bef-41e0-89c6-b55d0929964c}", "Ptr", &procthrottlemin)
VarSetCapacity(procthrottlemin1, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{893dee8e-2bef-41e0-89c6-b55d0929964d}", "Ptr", &procthrottlemin1)
VarSetCapacity(schedpolicy, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{93b8b6dc-0698-4d1c-9ee4-0644e900c85d}", "Ptr", &schedpolicy)
VarSetCapacity(shortschedpolicy, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{bae08b81-2d5e-4688-ad6a-13243356654b}", "Ptr", &shortschedpolicy)
VarSetCapacity(shortthreadarchclasslowerthreshold, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{53824d46-87bd-4739-aa1b-aa793fac36d6}", "Ptr", &shortthreadarchclasslowerthreshold)
VarSetCapacity(shortthreadarchclassupperthreshold, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{828423eb-8662-4344-90f7-52bf15870f5a}", "Ptr", &shortthreadarchclassupperthreshold)
VarSetCapacity(shortthreadruntimethreshold, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{d92998c2-6a48-49ca-85d4-8cceec294570}", "Ptr", &shortthreadruntimethreshold)
VarSetCapacity(smtunparkpolicy, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{b28a6829-c5f7-444e-8f61-10e24e85c532}", "Ptr", &smtunparkpolicy)
VarSetCapacity(softparklatency, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{97cfac41-2217-47eb-992d-618b1977c907}", "Ptr", &softparklatency)
VarSetCapacity(syscoolpol, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{94d3a615-a899-4ac5-ae2b-e4d8f634367f}", "Ptr", &syscoolpol)
VarSetCapacity(throttling, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", "{3b04d4fd-1cc7-4f23-ab1c-d1337819c4bb}", "Ptr", &throttling)

RegRead, OutputVar, HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Power\User\PowerSchemes, ActivePowerScheme
OutputVar:="{" OutputVar "}"
VarSetCapacity(scheme_current, 16, 0)
DllCall("ole32.dll\CLSIDFromString", "WStr", OutputVar, "Ptr", &scheme_current)

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
    DllCall("FreeLibrary", "Ptr", Ole32Module)
    Reset()
ExitApp

~^s::
    WinGetTitle, currentTitle, A
    if InStr(currentTitle, A_ScriptName)
        reload
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
}

ShellMessage(wParam, lParam) {
    Boost(1)
}

Boost(set) {
    global
    SetTimer, Reset, Off
    SetTimer, ResetDelay, Off
    AHKHID_Register(13, 5, 0, RIDEV_REMOVE)

    if timeout!=set
    {
        WinGet, exe, ProcessName, A
        WinGetTitle, title, A

        timeout:=set
        switch
        {
        case timeout=1:
            DllCall("powrprof.dll\PowerWriteDCValueIndex", "Ptr", 0, "Ptr", &scheme_current, "Ptr", &sub_processor, "Ptr", &procthrottlemax, "UInt", 100)
            DllCall("powrprof.dll\PowerWriteDCValueIndex", "Ptr", 0, "Ptr", &scheme_current, "Ptr", &sub_processor, "Ptr", &procthrottlemin, "UInt", 5)
            DllCall("powrprof.dll\PowerWriteDCValueIndex", "Ptr", 0, "Ptr", &scheme_current, "Ptr", &sub_processor, "Ptr", &cpmincores, "UInt", 20)
        case timeout=2:
            DllCall("powrprof.dll\PowerWriteDCValueIndex", "Ptr", 0, "Ptr", &scheme_current, "Ptr", &sub_processor, "Ptr", &procthrottlemax, "UInt", 100)
            DllCall("powrprof.dll\PowerWriteDCValueIndex", "Ptr", 0, "Ptr", &scheme_current, "Ptr", &sub_processor, "Ptr", &procthrottlemin, "UInt", 5)
            DllCall("powrprof.dll\PowerWriteDCValueIndex", "Ptr", 0, "Ptr", &scheme_current, "Ptr", &sub_processor, "Ptr", &cpmincores, "UInt", 20)
        }
        DllCall("powrprof.dll\PowerSetActiveScheme", "Ptr", 0, "Ptr", &scheme_current)
    }
    SetTimer, ResetDelay, -500
}

ResetDelay() {
    global
    if timeout=2
    {
        AHKHID_Register(13, 5, A_ScriptHwnd, RIDEV_INPUTSINK)
        SetTimer, Reset, -500
    }
    else
    {
        Boost(2)
    }
}

Reset() {
    global
    WinGet, exe, ProcessName, A
    WinGetTitle, title, A

    switch
    {
    default:
        DllCall("powrprof.dll\PowerWriteDCValueIndex", "Ptr", 0, "Ptr", &scheme_current, "Ptr", &sub_processor, "Ptr", &procthrottlemax, "UInt", 50)
        DllCall("powrprof.dll\PowerWriteDCValueIndex", "Ptr", 0, "Ptr", &scheme_current, "Ptr", &sub_processor, "Ptr", &procthrottlemin, "UInt", 0)
        DllCall("powrprof.dll\PowerWriteDCValueIndex", "Ptr", 0, "Ptr", &scheme_current, "Ptr", &sub_processor, "Ptr", &cpmincores, "UInt", 5)
    }
    timeout:=DllCall("powrprof.dll\PowerSetActiveScheme", "Ptr", 0, "Ptr", &scheme_current)
}
