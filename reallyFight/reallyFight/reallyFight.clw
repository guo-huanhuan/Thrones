; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=getmap
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "再快一点.h"

ClassCount=3
Class1=CMyApp
Class2=CMyDlg

ResourceCount=3
Resource2=IDD_MY_DIALOG
Resource1=IDR_MAINFRAME
Class3=getmap
Resource3=IDD_DIALOG1

[CLS:CMyApp]
Type=0
HeaderFile=再快一点.h
ImplementationFile=再快一点.cpp
Filter=N

[CLS:CMyDlg]
Type=0
HeaderFile=再快一点Dlg.h
ImplementationFile=再快一点Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CMyDlg



[DLG:IDD_MY_DIALOG]
Type=1
Class=CMyDlg
ControlCount=13
Control1=IDC_STATIC4,static,1342312960
Control2=IDC_STATIC3,static,1342312960
Control3=IDC_STATIC5,static,1342312960
Control4=IDOK,button,1342242817
Control5=IDCANCEL,button,1073807360
Control6=IDC_STATIC2,static,1342177806
Control7=IDC_EDIT1,edit,1350573060
Control8=IDC_STATIC0,static,1342177287
Control9=IDC_STATIC1,static,1342177287
Control10=IDC_STATIC7,static,1342312960
Control11=IDC_STATIC8,static,1342312960
Control12=IDC_STATIC9,static,1342312960
Control13=IDC_STATIC10,static,1342312960

[DLG:IDD_DIALOG1]
Type=1
Class=getmap
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_COMBO1,combobox,1344340225
Control4=IDC_STATIC,static,1342308865
Control5=IDC_BUTTON1,button,1342242816

[CLS:getmap]
Type=0
HeaderFile=getmap.h
ImplementationFile=getmap.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_BUTTON1

