Write-Output "-------------------------����CMakeĿ��--------------------------"
cmake -B build -S .

Write-Output "`n`n-------------------------����Ŀ��-------------------------------"
cmake --build build --config Release

Write-Output "`n`n-------------------------���в���-------------------------------"
#$env:NODE_OPTIONS="�Cmax-old-space-size=16384"
ts-node ./js/test.ts

Write-Output "�����ѽ��� �˳���: $LastExitCode"
