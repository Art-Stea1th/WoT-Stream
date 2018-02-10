#define AppName "WoT Stream: Remote"
#define AppVersion "0.0.1"
#define AppPublisher "Stanislav Kuzmich"
#define AppURL "https://github.com/Art-Stea1th/wot-stream/releases/latest"
#define AppExeName "wot_stream.exe"
#define AppCompatibleName "WoT Stream"

#define WoTRoot "{app}"
#define ResMods "res_mods\0.9.22.0"

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

UninstallFilesDir="{#WoTRoot}\{#CorePath}\"

[Files]
; Core files
Source: "core\*" ; DestDir: "{#WoTRoot}\{#CorePath}\";
Source: "resources\wot_icon.ico" ; DestDir: "{#WoTRoot}\{#CorePath}\";
Source: "core\{#CoreFiltersPath}\*" ; DestDir: "{#WoTRoot}\{#CorePath}\{#CoreFiltersPath}\";
; Mod files
Source: "mod\{#ModUIFilesPath}\*"; DestDir: "{#WoTRoot}\{#ResMods}\{#ModUIFilesPath}\";
Source: "mod\{#ModScriptsPath}\*"; DestDir: "{#WoTRoot}\{#ResMods}\{#ModScriptsPath}\";

[Icons]
Name: "{group}\{cm:ProgramOnTheWeb,{#AppCompatibleName}}"; Filename: "{#AppURL}";
Name: "{group}\{cm:UninstallProgram,{#AppCompatibleName}}"; Filename: "{uninstallexe}";

[Code]
function NextButtonClick(CurPageID: Integer): Boolean;
begin
  Result := True;
case CurPageID of
  wpSelectDir:
    if not FileExists(ExpandConstant('{#WoTRoot}\WorldOfTanks.exe')) then
    begin
      MsgBox('Invalid path to the World of Tanks folder', mbError, MB_OK);
      Result := False;
    end;
  end;
end;