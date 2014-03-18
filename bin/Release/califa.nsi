; califa.nsi
;--------------------------------

!include MUI2.nsh

; The name of the installer
Name "Califa"

; The file to write
OutFile "califa_inst.exe"

; The default installation directory
InstallDir $PROGRAMFILES\Califa

; Registry key to check for directory (so if you install again, it will
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\Califa" "Install_Dir"

; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------

; Pages

!insertmacro MUI_PAGE_LICENSE "license.rtf"
Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "Califa (requerido)"

  SectionIn RO

  ; Set output path to the installation directory.
  SetOutPath $INSTDIR

  ; Put file there
  File "califa.exe"
  File "license.txt"
  File "charset.dll"
  File "freetype6.dll"
  File "iconv.dll"
  File "intl.dll"
  File "libatk-1.0-0.dll"
  File "libatkmm-1.6-1.dll"
  File "libcairo-2.dll"
  File "libcairomm-1.0-1.dll"
  File "libexpat-1.dll"
  File "libfontconfig-1.dll"
  File "libgailutil-18.dll"
  File "libgdk_pixbuf-2.0-0.dll"
  File "libgdkmm-2.4-1.dll"
  File "libgdk-win32-2.0-0.dll"
  File "libgio-2.0-0.dll"
  File "libgiomm-2.4-1.dll"
  File "libglib-2.0-0.dll"
  File "libglibmm-2.4-1.dll"
  File "libgmodule-2.0-0.dll"
  File "libgobject-2.0-0.dll"
  File "libgthread-2.0-0.dll"
  File "libgtkmm-2.4-1.dll"
  File "libgtk-win32-2.0-0.dll"
  File "libjpeg-7.dll"
  File "libpango-1.0-0.dll"
  File "libpangocairo-1.0-0.dll"
  File "libpangoft2-1.0-0.dll"
  File "libpangomm-1.4-1.dll"
  File "libpangowin32-1.0-0.dll"
  File "libpng12-0.dll"
  File "libsigc-2.0-0.dll"
  File "libtiff-3.dll"
  File "zlib1.dll"

  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\Califa "Install_Dir" "$INSTDIR"

  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Califa" "DisplayName" "Califa"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Califa" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Califa" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Califa" "NoRepair" 1
  WriteUninstaller "uninstall.exe"

SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\Califa"
  CreateShortCut "$SMPROGRAMS\Califa\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\Califa\Califa.lnk" "$INSTDIR\califa.exe" "" "$INSTDIR\califa.exe" 0

SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"

  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Califa"
  DeleteRegKey HKLM SOFTWARE\Califa

  ; Remove files and uninstaller
  Delete "$INSTDIR\*.*"

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\Califa\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\Califa"
  RMDir "$INSTDIR"

SectionEnd
