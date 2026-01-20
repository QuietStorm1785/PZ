

# Build script for ProjectZomboidSwitch (PowerShell)
# Usage: .\build-switch.ps1 [-Target Switch|Windows|Linux] [-BuildType Release|Debug]

param(
    [ValidateSet("Switch", "Windows", "Linux")]
    [string]$Target,
    [string]$BuildType
)

if (-not $Target) { $Target = "Switch" }
if (-not $BuildType) { $BuildType = "Release" }

$MSYS2_BASH = "C:\devkitPro\msys2\usr\bin\bash.exe"
$PROJECT_DIR = "/c/PZ/PZ/ProjectZomboidSwitch"

Write-Host "=== Project Zomboid Build ===" -ForegroundColor Cyan
Write-Host "Target platform: $Target" -ForegroundColor Cyan

if ($Target -eq "Switch") {
    Write-Host "Launching MSYS2 and running build-switch.sh..." -ForegroundColor Cyan
    & $MSYS2_BASH -lc "cd $PROJECT_DIR && ./build-switch.sh switch $BuildType"
    Write-Host "Switch build finished. Check output in $PROJECT_DIR/build-switch" -ForegroundColor Green
} elseif ($Target -eq "Windows") {
    $winBuildDir = "build-windows"
    Write-Host "Configuring Windows build..." -ForegroundColor Cyan
    if (Test-Path $winBuildDir) { Remove-Item -Recurse -Force $winBuildDir }
    cmake -S . -B $winBuildDir -DCMAKE_BUILD_TYPE=$BuildType
    Write-Host "Building for Windows..." -ForegroundColor Cyan
    cmake --build $winBuildDir --config $BuildType
    Write-Host "Windows build finished. Check output in $winBuildDir" -ForegroundColor Green
} elseif ($Target -eq "Linux") {
    $linuxBuildDir = "build-linux"
    Write-Host "Configuring Linux build..." -ForegroundColor Cyan
    if (Test-Path $linuxBuildDir) { Remove-Item -Recurse -Force $linuxBuildDir }
    cmake -S . -B $linuxBuildDir -DCMAKE_BUILD_TYPE=$BuildType
    Write-Host "Building for Linux..." -ForegroundColor Cyan
    cmake --build $linuxBuildDir --config $BuildType
    Write-Host "Linux build finished. Check output in $linuxBuildDir" -ForegroundColor Green
}
