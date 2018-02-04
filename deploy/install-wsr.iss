#define AppName "WoT Stream: Remote"
#define AppVersion "0.0.1"
#define AppPublisher "Stanislav Kuzmich"
#define AppURL "https://github.com/Art-Stea1th/wot-stream"
#define AppExeName "wot_stream.exe"
#define AppCompatibleName "WoT Stream"

#define CoreFiltersPath "data\libobs"
#define ModUIFilesPath "gui\flash"
#define ModScriptsPath "scripts\client\gui\mods"

#define WoTRegistry "Software\Microsoft\Windows\CurrentVersion\Uninstall\{1EAC1D02-C6AC-4FA6-9A44-96258C37C812ru}_is1"
#define WoTVersion "0.9.21.0.3"

#define c_dir "{code:GetDir|0}"
#define m_dir "{code:GetDir|1}"

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

DefaultDirName={pf}\{#AppCompatibleName}\
CreateAppDir=True
DisableDirPage=True

DisableReadyPage=True
DisableReadyMemo=True

UninstallFilesDir={#c_dir}

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}";
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
; Core files
Source: "core\*" ; DestDir: "{#c_dir}";
Source: "resources\wot_icon.ico" ; DestDir: "{#c_dir}";
Source: "core\{#CoreFiltersPath}\*" ; DestDir: "{#c_dir}\{#CoreFiltersPath}\";
; Mod files
Source: "mod\{#ModUIFilesPath}\*"; DestDir: "{#m_dir}\{#WoTVersion}\{#ModUIFilesPath}\";
Source: "mod\{#ModScriptsPath}\*"; DestDir: "{#m_dir}\{#WoTVersion}\{#ModScriptsPath}\";

[Icons]
Name: "{group}\Start {#AppCompatibleName}"; Filename: "{#c_dir}\{#AppExeName}"; IconFilename: "{#c_dir}\wot_icon.ico";
Name: "{group}\{cm:ProgramOnTheWeb,{#AppCompatibleName}}"; Filename: "{#AppURL}";
Name: "{group}\{cm:UninstallProgram,{#AppCompatibleName}}"; Filename: "{uninstallexe}";
Name: "{commondesktop}\{#AppCompatibleName}"; Filename: "{#c_dir}\{#AppExeName}"; IconFilename: "{#c_dir}\wot_icon.ico"; Tasks: desktopicon;
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#AppCompatibleName}"; Filename: "{#c_dir}\{#AppExeName}"; Tasks: quicklaunchicon;

[Code]
var
  DirPage: TInputDirWizardPage;

function GetDir(Param: String): String;
begin
  Result := DirPage.Values[StrToInt(Param)];
end;

function GetWoTPath(): string;
var          
  WoTPath: string;
begin
  Result := 'C:\Games\World_of_Tanks\';
  if RegQueryStringValue(HKCU, '{#WoTRegistry}', 'InstallLocation', WoTPath) then
    Result := WoTPath + '\res_mods\'
end;

procedure InitializeWizard;
begin
  DirPage := CreateInputDirPage(wpSelectDir, 'Select Destination Location', 'Where should "{#AppName}" be installed?', '', False, '');
  DirPage.Add('Setup will install "{#AppName}" into the following folder:');
  DirPage.Add('Setup will install "mod" into the following "res_mods" folder:');
  DirPage.Values[0] := GetPreviousData('wot_stream', ExpandConstant('{pf}') + '\{#AppCompatibleName}');
  DirPage.Values[1] := GetPreviousData('res_mods', GetWoTPath());
end;

procedure RegisterPreviousData(PreviousDataKey: Integer);
begin
  SetPreviousData(PreviousDataKey, 'wot_stream', DirPage.Values[0]);
  SetPreviousData(PreviousDataKey, 'res_mods', DirPage.Values[1]);
end;