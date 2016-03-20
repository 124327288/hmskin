echo off
echo ---请确保拷贝前编译完Debug和Release两种模式
pause

xcopy /Y .\Win32\Debug\hmskin.dll ..\..\Win32\Debug\hmskin.dll
xcopy /Y .\Win32\Debug\hmskin.lib ..\..\Win32\Debug\lib\hmskin.lib
xcopy /Y .\Win32\Release\hmskin.dll ..\..\Win32\Release\hmskin.dll
xcopy /Y .\Win32\Release\hmskin.lib ..\..\Win32\Release\lib\hmskin.lib
xcopy /E /Y .\hmskin\inc\*.* ..\..\include\hmskin

echo ---拷贝完成
pause



