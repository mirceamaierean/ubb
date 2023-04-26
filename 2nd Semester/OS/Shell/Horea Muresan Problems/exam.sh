# Write a shell script that receives as command line arguments a character sequence S that does not contain whitespaces and, after the sequence S, there can be any number of arguments. For each argument after the sequence S:
# if the argument is a regular file, the script will report if the file contains the sequence S
# if the argument is a folder, the script will report if it contains an item (nonrecursive) with the name equal to the character sequence S (where item can be a file, folder, link, etc)
# else, the script will create a file in the current directory with the same name as the argument and the content equal to the sequence S
if [ ! $# -gt 0 ]; then
     echo "Provide at least one argument"
     exit 1 
fi
seq=$1
while [ $# -gt 1 ]; do
     if [ -f $2 ]; then
         if grep -E -q "^$seq$" $2; then
             echo "The file $2 contains $seq"
         else
             echo "The file $2 DOES NOT contain $seq"
         fi
     elif [ -d $2 ]; then
         val=$(ls $2 | grep -E -c "$seq")
         if [ $val -gt 0 ]; then
             echo "The folder $2 contains a file with the name of the sequence $seq"
         else
              echo "The folder $2 DOES NOT contain a file with the name of the sequence $seq"
         fi
     else
         echo $seq >> $2
     fi
     shift
done

