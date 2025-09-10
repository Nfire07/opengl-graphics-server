@echo off
setlocal

set "IMAGE_REF=opengl-graphics-server:latest"
set "CONTAINER_NAME=opengl-graphics-server"
set "VCXSERV_PATH=C:\Program Files\VcXsrv"
set "VCXSERV_EXE=vcxsrv.exe"

echo.
echo        ============================
echo    Checking if X server is running
echo        ============================
echo.

tasklist /FI "IMAGENAME eq %VCXSERV_EXE%" | find /I "%VCXSERV_EXE%" >nul
if %errorlevel% neq 0 (
    echo [INFO] X server not active. booting...
    start "" "%VCXSERV_PATH%\%VCXSERV_EXE%" :0 -multiwindow -ac -nowgl
    echo [INFO] Wait 3 seconds for VcXsrv to finish booting...
    timeout /t 3 /nobreak >nul
) else (
    echo [INFO] X server running...
)

echo.
echo        ============================
echo    Building container image %IMAGE_REF%
echo        ============================
echo.

docker build -t %IMAGE_REF% .

echo.
echo        ============================
echo    Running container image %IMAGE_REF%
echo        ============================
echo.

docker ps -a --filter "name=%CONTAINER_NAME%" --format "{{.ID}}" | findstr . >nul
if %errorlevel% equ 0 (
    docker rm -f %CONTAINER_NAME%
)

docker run -it --rm --name %CONTAINER_NAME% -e DISPLAY=host.docker.internal:0.0 -v "%cd%\src":/root/src %IMAGE_REF%

pause

cls

echo.
echo        ============================
echo    Stopping container image %IMAGE_REF%
echo        ============================
echo.

timeout /t 1 /nobreak >nul
endlocal
