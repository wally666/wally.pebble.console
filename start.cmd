@echo off
SET root_dir=%~dp0
SET project_name="wally.pebble.console"
SET host_name=%COMPUTERNAME%

echo Root Directory: %root_dir%
if "%project_name%" == "" (
   SET /p project_name="Enter the Project Name: "
)

echo Project Name: %project_name%
SET project_dir=%root_dir%
echo Project Directory: %project_dir%

:start
if not exist %project_dir% mkdir %project_dir%

SET "display=%host_name%:0.0"

:start
docker run -it --rm --net=host -e DISPLAY=%display% -v %project_dir%:/pebble/ bboehmke/pebble-dev /bin/bash -c "pebble build && pebble install --emulator aplite --logs"
if errorlevel 1 (
echo error 1
pause
goto start
)

:end
pause