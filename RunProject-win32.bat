mkdir build
cd build
cmake "Visual Studio 16 2019" "-A win32" ..
cmake --build .

cd ..
cd bin/Debug

app.exe
pause