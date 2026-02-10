@echo off
echo Building prebuilds for native-keyassassin...

REM Install dependencies
npm install

REM Build for all N-API versions and platforms
npm run prebuild-all

echo Prebuilds created successfully for native-keyassassin!
echo Files are located in the lib/binding directory
pause