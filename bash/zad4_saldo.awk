BEGIN {
FS = ",";
}

{
	if ( NR > 1 ){

	kwota[NR] = $4;
	saldo[NR] = $6;



		if ( $4 == "-" || $6 == "-" ){
		print ("Błąd, pole w wierszu  jest puste wiersz :", NR)
		}
}



}
END{
	for ( i = 3; i <= NR; i++){
		if ( saldo[i] == (saldo[i-1]) + (kwota[i]) ){
			print saldo[i], saldo [i-1], kwota[i]," dobrze \n ";}
		if ( saldo[i] != (saldo[i-1]) + (kwota[i]) ){
			print saldo[i], saldo[i-1],kwota[i],"bład w wierszu", i,"\n";}
}
}
