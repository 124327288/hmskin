echo off
echo ---��ȷ������ǰ������Debug��Release����ģʽ
pause

xcopy /Y .\Win32\Debug\hmskin.dll ..\..\Win32\Debug\hmskin.dll
xcopy /Y .\Win32\Debug\hmskin.lib ..\..\Win32\Debug\lib\hmskin.lib
xcopy /Y .\Win32\Release\hmskin.dll ..\..\Win32\Release\hmskin.dll
xcopy /Y .\Win32\Release\hmskin.lib ..\..\Win32\Release\lib\hmskin.lib
xcopy /E /Y .\hmskin\inc\*.* ..\..\include\hmskin

echo ---�������
pause



