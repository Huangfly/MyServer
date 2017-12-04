# Microsoft Developer Studio Project File - Name="VODServer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=VODServer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VODServer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VODServer.mak" CFG="VODServer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VODServer - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "VODServer - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VODServer - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "VODServer - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "VODServer - Win32 Release"
# Name "VODServer - Win32 Debug"
# Begin Group "main"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\makefile
# End Source File
# End Group
# Begin Group "net"

# PROP Default_Filter ""
# Begin Group "CSocket"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CSocket\CSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\CSocket\CSocket.h
# End Source File
# Begin Source File

SOURCE=.\CSocket\CTcpSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\CSocket\CTcpSocket.h
# End Source File
# Begin Source File

SOURCE=.\CSocket\CUdpSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\CSocket\CUdpSocket.h
# End Source File
# End Group
# Begin Group "CEpoll"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CEpoll\CClientEpoll.cpp
# End Source File
# Begin Source File

SOURCE=.\CEpoll\CClientEpoll.h
# End Source File
# Begin Source File

SOURCE=.\CEpoll\CEpollBase.cpp
# End Source File
# Begin Source File

SOURCE=.\CEpoll\CEpollBase.h
# End Source File
# Begin Source File

SOURCE=.\CEpoll\CServerEpoll.cpp
# End Source File
# Begin Source File

SOURCE=.\CEpoll\CServerEpoll.h
# End Source File
# End Group
# Begin Group "CStreamBase"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CStreamBase\CStreamBase.cpp
# End Source File
# Begin Source File

SOURCE=.\CStreamBase\CStreamBase.h
# End Source File
# End Group
# Begin Group "CPacket"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CPacket\packet.cpp
# End Source File
# Begin Source File

SOURCE=.\CPacket\packet.h
# End Source File
# End Group
# Begin Group "CServer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CServer\CTcpServer.cpp
# End Source File
# Begin Source File

SOURCE=.\CServer\CTcpServer.h
# End Source File
# End Group
# Begin Group "CClient"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CClient\CTcpClient.cpp
# End Source File
# Begin Source File

SOURCE=.\CClient\CTcpClient.h
# End Source File
# End Group
# Begin Group "CHostAddr"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CHostAddr\CHostAddr.cpp
# End Source File
# Begin Source File

SOURCE=.\CHostAddr\CHostAddr.h
# End Source File
# End Group
# Begin Group "CThread"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CThread\CThreadBase.cpp
# End Source File
# Begin Source File

SOURCE=.\CThread\CThreadBase.h
# End Source File
# Begin Source File

SOURCE=.\CThread\CThreadPool.cpp
# End Source File
# Begin Source File

SOURCE=.\CThread\CThreadPool.h
# End Source File
# End Group
# Begin Group "CShareMem"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CShareMem\CShareMem.cpp
# End Source File
# Begin Source File

SOURCE=.\CShareMem\CShareMem.h
# End Source File
# End Group
# Begin Group "CLog"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CLog\CLog.cpp
# End Source File
# Begin Source File

SOURCE=.\CLog\CLog.h
# End Source File
# End Group
# End Group
# Begin Group "CPreServer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CPreServer\CPreServer.cpp
# End Source File
# Begin Source File

SOURCE=.\CPreServer\CPreServer.h
# End Source File
# End Group
# Begin Group "CBackServer"

# PROP Default_Filter ""
# Begin Group "CLoginTask"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CBackServer\CLoginTask\CLoginTask.cpp
# End Source File
# Begin Source File

SOURCE=.\CBackServer\CLoginTask\CLoginTask.h
# End Source File
# End Group
# Begin Group "CVideoChannelTask"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CBackServer\CVideoChannelTask\CVideoChannelTask.cpp
# End Source File
# Begin Source File

SOURCE=.\CBackServer\CVideoChannelTask\CVideoChannelTask.h
# End Source File
# End Group
# Begin Group "CVideoListTask"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CBackServer\CVideoListTask\CVideoListTask.cpp
# End Source File
# Begin Source File

SOURCE=.\CBackServer\CVideoListTask\CVideoListTask.h
# End Source File
# End Group
# Begin Group "CVideoRegionTask"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CBackServer\CVideoRegionTask\CVideoRegionTask.cpp
# End Source File
# Begin Source File

SOURCE=.\CBackServer\CVideoRegionTask\CVideoRegionTask.h
# End Source File
# End Group
# Begin Group "CVideoTypeTask"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CBackServer\CVideoTypeTask\CVideoTypeTask.cpp
# End Source File
# Begin Source File

SOURCE=.\CBackServer\CVideoTypeTask\CVideoTypeTask.h
# End Source File
# End Group
# Begin Group "CPlayTask"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CBackServer\CPlayTask\CPlayTask.cpp
# End Source File
# Begin Source File

SOURCE=.\CBackServer\CPlayTask\CPlayTask.h
# End Source File
# End Group
# Begin Group "CPlayTimeTask"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CBackServer\CPlayTimeTask\CPlayTimeTask.cpp
# End Source File
# Begin Source File

SOURCE=.\CBackServer\CPlayTimeTask\CPlayTimeTask.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\CBackServer\CBackServer.cpp
# End Source File
# Begin Source File

SOURCE=.\CBackServer\CBackServer.h
# End Source File
# Begin Source File

SOURCE=.\CBackServer\CUnpackTask.cpp
# End Source File
# Begin Source File

SOURCE=.\CBackServer\CUnpackTask.h
# End Source File
# End Group
# Begin Group "DB"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DB\Init.sql
# End Source File
# End Group
# Begin Group "DbCon"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DbCon\DbCon.cpp
# End Source File
# Begin Source File

SOURCE=.\DbCon\DbCon.h
# End Source File
# End Group
# End Target
# End Project
