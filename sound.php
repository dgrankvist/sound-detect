<?php
$log_file = 'sound_log.txt';
$levels_file = 'levels.txt';
$data = $_POST['data'];
$today = date("Y-m-d H:i:s");
$str = $today.', '.$data."\n"; 
$jsondata = json_encode($today)."!".json_encode($data)."\n"; // ! chosen as arbitrary character to separate timestamp from data values
// echo "This is from the server \n";
// now we open the file
if(file_exists($log_file)){
	$fp=fopen($log_file,a); // The file is opened as append mode
	fwrite($fp, $str);
	fclose($fp);
}else{ // The file doesn't exist, so open a new one. 
	$fp=fopen($log_file,w); 
	fwrite($fp, $str);
	fclose($fp);
}
// open the file that stores the current decibel levels. 
// Always open in write mode to overwrite previous data.
$fr=fopen($levels_file,w);
fwrite($fr, $jsondata);
fclose($fr);

echo "Data is stored.\n";
?>
