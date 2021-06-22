echo off

setlocal EnableDelayedExpansion

set /a value=0

for %%f in (*.png) do (
	rename %%f !value!.png
	set /a value=value+1
)
echo on