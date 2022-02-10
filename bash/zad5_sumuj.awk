BEGIN{FS=" ";}

{
	arr[$1 , $2 , $3] += $4;
}
END{

for (i in arr){
print i, arr[i];
}}
