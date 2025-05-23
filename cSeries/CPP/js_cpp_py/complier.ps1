Write-Output "-------------------------加载CMake目标--------------------------"
cmake -B build -S .

Write-Output "`n`n-------------------------编译目标-------------------------------"
cmake --build build --config Release

Write-Output "`n`n-------------------------移到pyd文件---------------------------"
Move-Item -Path build\Release\bridge.pyd -Destination .\py\bridge.pyd

Write-Output "`n`n-------------------------运行测试-------------------------------"
python .\py\test.py

Write-Output "进程已结束 退出码: $LastExitCode"