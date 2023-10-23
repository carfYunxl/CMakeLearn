mkdir build
cd build
cmake "Visual Studio 17 22022" "-A win32" ..
cmake --build .

cd ..
cd bin/Debug

app.exe
pause