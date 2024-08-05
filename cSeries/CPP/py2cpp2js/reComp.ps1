Write-Output "-------------------------加载CMake目标--------------------------"
cmake -B build -S .

Write-Output "`n`n-------------------------编译目标-------------------------------"
cmake --build build --config Release

Write-Output "`n`n-------------------------运行测试-------------------------------"
ts-node ./node/test.ts

Write-Output "进程已结束"
