<?php
$myfile = fopen("db.txt", "w");
$time = date('F j, Y, H:i:s');
$database = fopen("data.txt", "a");
if(.!empty($_POST)){
	for($i = 1; $i <= 8 ; $i++)
	{	
		echo "df".$i."=".trim($_POST["df".$i])." ";
		fwrite($myfile,trim($_POST["df".$i])." ");
	}


	for($j = 1; $j <=8; $j++)
	{
		fwrite($database,$time.": ".trim($_POST["df".$j]."  |"));
	} }
else{
file_put_contents("$myfile", "");
}
echo $time."<br>";
?>
if 