show_process_info() {
  local pid=$1
  local isfd=$2
  if ps -p $pid > /dev/null 2>&1; 
  	then
    printf "Name: %s\n" "$(ps -p $pid -o comm=)"
    printf "PID:  %d\n" $pid
    printf "PPID: %s\n" "$(ps -o ppid= -p $pid)"
    if [ "$isfd" = "fd" ]; 
		  then
      echo -n "FD:"
      ls -l "/proc/$pid/fd" | awk '{print $9}'
    elif [ "$isfd" != "" ]; 
		  then
      echo "Неверное значение второго параметра. Допустимо только 'fd'."
    fi
  else
    echo "Процесс $pid не найден"
  fi
}

if [ $# -eq 1 ]; 
	then
  pid=$1
  show_process_info $pid
elif [ $# -eq 2 ]; 
	then
  pid=$1
  isfd=$2
  show_process_info $pid $isfd
else
  echo "Неверное количество параметров"
fi
