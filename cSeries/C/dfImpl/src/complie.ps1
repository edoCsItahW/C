Set-Location dy
cmake -B build -S .
cmake --build build --config Release
Remove-Item -Path build -Recurse -Force
Set-Location ../st
cmake -B build -S .
cmake --build build --config Release
Remove-Item -Path build -Recurse -Force