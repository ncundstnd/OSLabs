@echo off
@chcp 65001
@echo Все параметры %*
@echo Первый параметр: %1
@echo Второй параметр: %2
@echo Третий параметр: %3

set /a result=%1 %3 %2

@echo result = %result%

Pause