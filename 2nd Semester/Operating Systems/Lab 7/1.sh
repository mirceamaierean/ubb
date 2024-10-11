# Write a bash script that takes any number of usernames as command linea rguments. You do not need to validate that the provided arguments are correct usernames. The script will print once a second the total number of processes per user. If no arguments are given, the script should print a message and then will terminate.
if [ $# -eq 0 ]; then
   echo "No arguments passed"
   exit 1
fi
while true; do
  for a; do
      ps -u $a | awk -F, 'END{print NR}'
  done
  sleep 1
done