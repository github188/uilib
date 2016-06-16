; Script generated by the Inno Script Studio Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Launcher"
#define MyAppVersion "1.0.0.1.2"
#define MyAppPublisher "sisec"
#define MyAppURL "http://www.sisec.com.cn/"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId=FC1004DE-2231-4194-9991-4E36E3155B76
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
OutputBaseFilename=������{#MyAppVersion}
Compression=lzma
SolidCompression=yes

[Languages]
Name: "ch"; MessagesFile: "compiler:Languages\ChineseSimplified.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags:checkablealone;
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}";

[Files]
Source: "..\bin\Launcher.exe"; DestDir: "{app}"; Flags: ignoreversion 
Source: "..\bin\DuiLib.dll"; DestDir: "{app}"; Flags: ignoreversion 
Source: "..\bin\msvcr120.dll"; DestDir: "{app}"; Flags: ignoreversion 
Source: "..\bin\skin\launcher\*"; DestDir: "{app}\skin\launcher\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\bin\skin\menu.xml"; DestDir: "{app}\skin\"; Flags: ignoreversion 
Source: "..\bin\skin\launcher.xml"; DestDir: "{app}\skin\"; Flags: ignoreversion 
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

[UninstallDelete]
Type: files;          Name: "{app}\*.json"
Type: filesandordirs; Name: "{app}"
