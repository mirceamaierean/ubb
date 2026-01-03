#!/bin/bash
while read X; do
 if echo "$X" | grep -E -q "^[^+-]+([+-][^+-]+)+$"; then
 echo "$X" | sed -E "s/[^0-9+-]//g" | sed -E "s/([+-])/ \1 /g"
 fi
done < a.txt | while read A B C; do
 expr $A $B $C
done
