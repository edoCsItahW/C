Write-Output "-------------------------����CMakeĿ��--------------------------"
cmake -B build -S .

Write-Output "`n`n-------------------------����Ŀ��-------------------------------"
cmake --build build --config Release

Write-Output "`n`n-------------------------�Ƶ�pyd�ļ�---------------------------"
Move-Item -Path build\Release\bridge.pyd -Destination .\py\bridge.pyd

Write-Output "`n`n-------------------------���в���-------------------------------"
python .\py\test.py

Write-Output "�����ѽ��� �˳���: $LastExitCode"