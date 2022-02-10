if [ "$#" -eq "1" ]
then
	for x in *$1
	do

		cp -p "$x" $HOME/.arch/`echo $x | sed s/$1/_arch$1/`
	done
fi
