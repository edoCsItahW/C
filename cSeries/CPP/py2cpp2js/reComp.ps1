Write-Output "-------------------------����CMakeĿ��--------------------------"
cmake -B build -S .

Write-Output "`n`n-------------------------����Ŀ��-------------------------------"
cmake --build build --config Release

Write-Output "`n`n-------------------------���в���-------------------------------"
ts-node ./node/test.ts

Write-Output "�����ѽ���"
