
if test "$1" = "-a"
then
	for x in "$@"
		do
		ls -1 -a "$x" | wc -l
		done
		fi
if [ "$1" != "-a" ]
then
	ls -1 | wc -l
fi
