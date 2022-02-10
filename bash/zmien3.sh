for x in "$@"
do
	if expr "$x" : '.*\.c$' > /dev/null
	then
		y=`echo "$x" | sed s/.c/_org.c/`
		mv "$x" "$y"
	else
		echo "$x plik nie ma dobrej koncowki"
	fi
done



