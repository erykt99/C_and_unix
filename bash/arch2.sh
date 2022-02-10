if [ "$#" -eq "1" ]
then
	for x in *$1
	do
		cp -p $x $HOME/.arch/`basename $x $1`_arch$1
	done
fi

