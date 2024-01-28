@echo off
@chcp 65001
if "%*" == "" (goto null) else (goto notnull)

:null
echo — Строка параметров:
echo — Режим: %1
echo — Имя файла: %2
echo —-+ %~n0 Режим файла
echo —-++ Режим = {создать, удалить}
echo —-++ Файл = имя файла
goto exit

:notnull
if not "%2" == "" goto file else goto nofile

:nofile
echo — Строка параметров: %*
echo — Режим: %1
echo — Имя файла: %2
echo —-+ Не задано имя файла
goto exit

:file
if "%1" == "создать" goto create
if "%1" == "удалить" goto delete else goto failmode

:failmode
echo — Строка параметров: %*
echo — Режим: %1
echo — Имя файла: %2
echo —-+ Режим задан некорректно
goto exit

:create
if exist %2 goto foundfile else goto createfile
goto createfile

:delete
if exist %2 goto deletefile else goto notfoundfile

:notfoundfile
echo — Строка параметров: %*
echo — Режим: %1
echo — Имя файла: %2
echo —-+ Файл %2 не найден
goto exit

:foundfile
echo — Строка параметров: %*
echo — Режим: %1
echo — Имя файла: %2
echo —-+ Файл %2 уже есть
goto exit

:createfile
copy /b NUL %2
echo — Строка параметров: %*
echo — Режим: %1
echo — Имя файла: %2
echo —-+ Файл %2 создан
goto exit

:deletefile
del %2
echo — Строка параметров: %*
echo — Режим: %1
echo — Имя файла: %2
echo —-+ Файл %2 удален
goto exit

:exit

Pause