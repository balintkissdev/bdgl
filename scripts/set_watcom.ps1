$scriptsDir = split-path -parent $MyInvocation.MyCommand.Path
$projectDir = (get-item $scriptsDir).parent.FullName
$depsDir = Join-Path $projectDir 'deps'
$watcomDir = Join-Path $depsDir 'open-watcom-v2'

if ($env:WATCOM -eq $watcomDir)
{
    Write-Output 'Open Watcom build environment was already set. Use "wmake" to build the library.'
    exit 0
}

if ($env:PROCESSOR_ARCHITECTURE -eq 'AMD64') {
    $osText = 'Windows 64-bit'
    $watcomBindirs = "$(Join-Path $watcomDir 'binnt64');$(Join-Path $watcomDir 'binnt')"
} else {
    $osText = 'Windows 32-bit'
    $watcomBindirs = "$(Join-Path $watcomDir 'binnt');$(Join-Path $watcomDir 'binw')"
}

$env:WATCOM = $watcomDir
$env:Path = "$watcomBindirs;$env:Path"
$env:EDPATH = "$watcomDir/eddat"
$env:WIPFC = "$watcomDir/wipfc"
$env:INCLUDE = "$watcomDir/h"

Write-Output "Watcom root: $env:WATCOM"
Write-Output "System: $osText"
Write-Output "Watcom binaries: $watcomBindirs"
Write-Output ""
Write-Output 'Open Watcom build environment is set! Use "wmake" to build the library.'
