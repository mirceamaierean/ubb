A=""
if test $A; then
    echo "A is not empty"
else
    echo "A is empty"
fi

B=$(echo $A | grep -E -c -v "^.+$")
echo $B
if test $B -eq 1; then
    echo "A is empty"
fi

B=$(echo $A | awk '{print length}')
echo $B
if test $B -eq 0; then
    echo "A is empty"
fi

if test $A=""; then
    echo "A is empty"
fi

if test -z $A; then
    echo "A is empty"
fi

if test ${#A} -eq 0; then
    echo "A is empty"
fi

if test ! ${#A} -gt 0; then
    echo "A is empty"
fi


file="not_exist.txt"

if test ! -e $file; then
    echo "file not exist"
fi

if test $(ls $file 2>&1 | grep -E -c "No such file") -eq 1; then
    echo "file not exist"
else
    echo "file exist"
fi

file2="test_empty2.sh"
# test condition using grep -q
if $(ls $file2 2>&1 | grep -E -q "No such file"); then
    echo "file not exist"
else
    echo "file exist"
fi
