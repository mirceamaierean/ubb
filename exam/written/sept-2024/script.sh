RE='^(.*)([+-]) (-?[0-9]+) (-?[0-9]+)(.*)$'
L="$1"
while true; do
 if echo $L | grep -q -v -E "$RE"; then
 exit 1
 fi
 A=`echo $L | sed -E "s/$RE/\1/"`
 B=`echo $L | sed -E "s/$RE/\3 \2 \4/"`
 C=`echo $L | sed -E "s/$RE/\5/"`
 L="$A     `expr $B`     $C"
 echo "A='$A' B='$B' C='$C'"
echo $L
 if echo $L | grep -E -q "^ *-?[0-9]+ *$"; then
 break
 fi
done
echo $L
