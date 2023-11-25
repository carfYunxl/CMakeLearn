mkdir build
cd build
cmake "Visual Studio 17 22022" "-A win32" ..
cmake --build . --config Release

cd ..
cd bin/Release

GEditor.exe
pause