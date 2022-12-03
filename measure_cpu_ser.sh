#!/bin/bash
ranges=(
    "100 1000 10000 100000 1000000
    10000000 20000000 30000000 40000000
    50000000 60000000 70000000 80000000
    90000000 100000000 110000000 120000000
    130000000 140000000 150000000 160000000
    170000000 180000000 190000000 200000000"
)
csv_output="${range}"
for range in $ranges; do
    output=$(./serial_cpu -n ${range} -silent)
    csv_output="${range}"
    for val in $output; do
        if [[ ! $val == c:* ]]; then
            csv_output="${csv_output},${val}"
        fi
    done
    echo $csv_output
done
