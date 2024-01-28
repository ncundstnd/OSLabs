@echo off
@chcp 65001
@echo Название исполняемого BAT-файла: %~n0
for /f "tokens=1-5 delims=.: " %%j in ('
 dir/a-d/tc "%~f0"^| findstr/rc:"^[^ ]"
') do (
 set mydate=%%l.%%k.%%j
 set mytime=%%m:%%n )
@echo Дата и время создания исполняемого BAT-файла: %mydate% %mytime%
@echo Путь к исполняемуму BAT-файлу: %~f0

Pause