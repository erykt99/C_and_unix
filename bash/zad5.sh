
DZIEN=`date +%u`
if [ $DZIEN -ge 6 ] ;
then
echo "Have a nice weekend"
else
echo "Have a nice week"
fi