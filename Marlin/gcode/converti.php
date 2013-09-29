#!/usr/bin/php -q
<?PHP
$names=Array( "SharebotNG_LevelPlate_Auto.gcode",  "SharebotNG_FilamentChange_L.gcode",  "SharebotNG_FilamentChange_R.gcode",  "SharebotNG_LevelPlate_Man.gcode",  "SharebotNG_Nozzles.gcode" );
$out=Array(   "sc_level_plate_a.h",            "sc_change_left.h",            "sc_change_right.h",            "sc_level_plate_m.h",            "sc_nozzles.h" );
$vars=Array(  "LEVEL_PLATE_A",		     "CHANGE_LEFT",		  "CHANGE_RIGHT",			"LEVEL_PLATE_M",		       "NOZZLES" );

print_r( $names );

foreach ( $names as $pos=>$name ) {
	$var_name=$vars[$pos];
	$output=$out[$pos];
	echo "$pos - $name -> $output ( $var_name)\n";
	$fp=fopen( $name, "rb" );
	$fpw=fopen( $output, "w+b" );
	$first=true;
	$cnt=0;
	if ( $fp != NULL ) {
   		echo "#ifndef SC_".$var_name."\n";
		fwrite ( $fpw, "#ifndef SC_".$var_name."\n" );
   		echo "#define SC_".$var_name."\n";
		fwrite ( $fpw, "#define SC_".$var_name."\n" );
   		echo "static uint8_t ".$var_name."[] = {";
		fwrite ( $fpw, "static uint8_t ".$var_name."[] = {" );
  	 	while ( !feof($fp) ) {
      			$c = fgetc($fp);
      			$cnt++;
      			if ( $cnt == 1 )
         			$first=false;
      			else {
         			echo ",";
				fwrite ( $fpw, "," );
			}
      			echo ord($c);
			fwrite ( $fpw, ord($c) );
   		}
   		echo "};\n";
		fwrite ( $fpw, "};\n" );
   		echo "#define ".$var_name."_LENGTH ".($cnt-1)."\n";
		fwrite ( $fpw, "#define ".$var_name."_LENGTH ".($cnt-1)."\n" );
   		echo "#endif\n";
		fwrite ( $fpw, "#endif\n" );
	}
	fclose ( $fp );
	fclose ( $fpw );
}
?>
