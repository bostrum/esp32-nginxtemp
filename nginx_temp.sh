#!/bin/bash
LOG_FILE="/srv/nginx/logs/access.log"
OUTPUT_FILE="/srv/nginx/html/temp.txt"

# get time and temp from nginx access log
latest_entry=$(grep 'badtemp' "$LOG_FILE" | tail -n 1)
timestamp=$(echo "$latest_entry" | grep -oP '\d{2}/\w{3}/\d{4}:\d{2}:\d{2}:\d{2}')
temperature=$(echo "$latest_entry" | grep -oP 'badtemp=\K[\d.]+')

# get date from nginx format
month_map=("Jan" "Feb" "Mar" "Apr" "May" "Jun" "Jul" "Aug" "Sep" "Oct" "Nov" "Dec")
month_abbr=$(echo "$timestamp" | cut -d'/' -f2)
month_num=0
for i in "${!month_map[@]}"; do
  if [[ "${month_map[$i]}" == "$month_abbr" ]]; then
    month_num=$((i + 1))
    break
  fi
done
month_num_padded=$(printf "%02d" "$month_num")
day=$(echo "$timestamp" | cut -d'/' -f1)
year=$(echo "$timestamp" | cut -d'/' -f3 | cut -d':' -f1)
hour_minute_second=$(echo "$timestamp" | cut -d':' -f2-)

# write date in iso 8601 format and temp to .txt
date_formatted="${year}-${month_num_padded}-${day} ${hour_minute_second}"
echo "$date_formatted;$temperature;" > "$OUTPUT_FILE"
