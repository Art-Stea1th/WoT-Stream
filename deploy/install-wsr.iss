#define AppName "WoT Stream: Remote"
#define AppVersion "0.0.1"
#define AppPublisher "Stanislav Kuzmich"
#define AppURL "https://github.com/Art-Stea1th/wot-stream/releases/latest"
#define AppExeName "wot_stream.exe"
#define AppCompatibleName "WoT Stream"

#define WoTRegistry "Software\Microsoft\Windows\CurrentVersion\Uninstall\{1EAC1D02-C6AC-4FA6-9A44-96258C37C812ru}_is1"

#define Destination "{code:GetWoTPath|'C:\Games\World_of_Tanks\'}\res_mods\0.9.22.0"

#define CorePath "wot_stream"
#define CoreFiltersPath "data\libobs"

#define ModUIFilesPath "gui\flash"
#define ModScriptsPath "scripts\client\gui\mods"

[Setup]
AppId={{4BECE10F-1F54-4846-8FF5-1E4B7952F6FE}
AppName={#AppName}
AppVersion={#AppVersion}
AppPublisher={#AppPublisher}
AppPublisherURL={#AppURL}
AppSupportURL={#AppURL}
AppUpdatesURL={#AppURL}
DefaultGroupName={#AppCompatibleName}
AllowNoIcons=False
OutputDir=".\"

OutputBaseFilename=install-wsr
Compression=lzma2/ultra64
SolidCompression=yes
InternalCompressLevel=ultra64

RestartIfNeededByRun=False

SetupIconFile=resources\wot_icon.ico
UninstallDisplayIcon={uninstallexe}

DefaultDirName=C:\Games\World_of_Tanks\
AppendDefaultDirName=False
DirExistsWarning=False
DisableDirPage=False

DisableReadyPage=True
DisableReadyMemo=True

UninstallFilesDir="{#Destination}\{#CorePath}\"

[Files]
; Core files
Source: "core\*" ; DestDir: "{#Destination}\{#CorePath}\";
Source: "resources\wot_icon.ico" ; DestDir: "{#Destination}\{#CorePath}\";
Source: "core\{#CoreFiltersPath}\*" ; DestDir: "{#Destination}\{#CorePath}\{#CoreFiltersPath}\";
; Mod files
Source: "mod\{#ModUIFilesPath}\*"; DestDir: "{#Destination}\{#ModUIFilesPath}\";
Source: "mod\{#ModScriptsPath}\*"; DestDir: "{#Destination}\{#ModScriptsPath}\";

[Icons]
Name: "{group}\{cm:ProgramOnTheWeb,{#AppCompatibleName}}"; Filename: "{#AppURL}";
Name: "{group}\{cm:UninstallProgram,{#AppCompatibleName}}"; Filename: "{uninstallexe}";

[Code]

function GetWoTPath(default: String): string;
var          
  WoTPath: string;
begin
  Result := default;
  if RegQueryStringValue(HKCU, '{#WoTRegistry}', 'InstallLocation', WoTPath) then
    Result := WoTPath
end;

function NextButtonClick(CurPageID: Integer): Boolean;
begin
  Result := True;
case CurPageID of
  wpSelectDir:
    if not FileExists(ExpandConstant('{app}\WorldOfTanks.exe')) then
    begin
      MsgBox('Invalid path to the World of Tanks folder', mbError, MB_OK);
      Result := False;
    end;
  end;
end;