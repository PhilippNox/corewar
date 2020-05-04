#!/bin/sh

path="vm_champs/champs"
#path="vm_champs/test"
tm=1
from=0
source="0_tscan_timeout"
max_dump=999999
tmp_out="run_out"
tmp_run="run_tmp"

echo "example:"
echo "./tscan.sh -t 1 -s 0_tscan_timeout"

while getopts 't:s:f:' opts; do
	case "${opts}" in
		t) tm=${OPTARG} ;;
		s) source=${OPTARG} ;;
    f) from=${OPTARG} ;;
	esac
done

run_with_timeout() {
  f_val="./tbinary.sh -a $champ_a -b $champ_b -v 14 -d $max_dump"
  echo $f_val > $tmp_out
  $f_val > $tmp_run 2>&1 &
  PID=$!

  (sleep $tm ; kill -9 $PID &> /dev/null; echo "timeout_kill" >> $tmp_out;) &
  PID_KILLER=$!

  # for check use:  ps aux | grep 'name of program in f_val'
  wait $PID &> /dev/null

  kill -9 $PID_KILLER &> /dev/null
  wait $PID_KILLER 2>/dev/null

  pid_core=$(pgrep corewar)
  kill -9 $pid_core &> /dev/null
  wait $pid_core 2>/dev/null

  echo "done" >> $tmp_out
}

log_no_timeout() {
  name_test=$(tail -1 run_tmp)
  state=$(tail -2 run_tmp | head -1)
  if [[ $state == *"✅"* ]]; then
    echo $f_val >> ${tm}_tscan_done_diff_ok
    echo "\t✅"
  elif [[ $state == *"🏁"* ]]; then
    echo $f_val >> ${tm}_tscan_done_finish
    echo "\t🏁️"
  else
    echo $f_val >> ${tm}_tscan_done_diff_bad
    echo "\t⚠"
  fi
}

log() {
  name_test=$(head -1 run_out)
  is_time_out=$(head -2 run_out | tail -1)
  if [[ $is_time_out == *"timeout_kill"* ]]; then
    echo "$champ_a $champ_b" >> ${tm}_tscan_timeout
    echo "\t⌛️"
  else
    log_no_timeout
  fi
}

init() {
  rm 0_tscan_timeout 2> /dev/null
  for champ_a in $(ls $path | cut -d '.' -f 1)
  do
    for champ_b in $(ls $path | cut -d '.' -f 1)
    do
      echo "$champ_a $champ_b" >> 0_tscan_timeout
    done
  done
}

#init; exit 1

if [ "$from" -eq "0" ]; then
    rm ${tm}_tscan_done_finish 2> /dev/null
    rm ${tm}_tscan_done_diff_ok 2> /dev/null
    rm ${tm}_tscan_done_diff_bad 2> /dev/null
    rm ${tm}_tscan_timeout 2> /dev/null
fi
idx=0
while read line; do
  idx=$((idx + 1))
  if [ "$idx" -le "$from" ]; then
    continue
  fi
  echo "$idx \t$line"
  champ_a=$(echo $line | cut -d ' ' -f 1)
  champ_b=$(echo $line | cut -d ' ' -f 2)
  run_with_timeout
  log
  echo "\t\tFor continue use this: ./tscan.sh -t $tm -s $source -f $idx"
done < $source