<?php
	if(isset($_GET['adresse'])){
	$adresse = $_GET['adresse'];}
	else{$adresse = "1645 Route des Lucioles Biot";}/*Adresse par défaut*/
	
	$url = "http://nominatim.openstreetmap.org/search?format=json&polygon=1&addressdetails=1&q=".urlencode($adresse);
	
	/*User Agent*/
	$opts = array('http'=>array('header'=>"User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/13.0.782.112 Safari/535.1 \r\n"));
    $context = stream_context_create($opts);
    
	$jsonBrut = file_get_contents($url,false, $context);
	/*$jsonBrut = file_get_contents("data2.json");*/
	$jsonDecode = json_decode($jsonBrut);
	
	foreach($jsonDecode as $area){ /*On itère sur les différents lieux que nous retourne nominatim (dans le cas où on a plusieurs lieux*/
		$lat = $area->lat; /*jsonDecode[0] est un objet et lat est un attribut*/
		$lon = $area->lon;
		$boundingbox = $area->boundingbox; /*boundingbox est un array à 4 valeurs*/
	
		$urlMeteo = "http://api.openweathermap.org/data/2.5/weather?lang=fr&units=metric&lat=$lat&lon=$lon&APPID=1dc250956d9b1464e48dd58f63d25cfb";
		/* http://api.openweathermap.org/data/2.5/weather?lang=fr&units=metric&lat=43.7050294&lon=7.2818662&APPID=1dc250956d9b1464e48dd58f63d25cfb */
		$meteoBrut = file_get_contents($urlMeteo,false, $context);
		$meteoDecode = json_decode($meteoBrut);
	
		/* Attention, pas la même hierarchie que le fichier json nominatim*/

		$nom = $meteoDecode->name;
		$icon = $meteoDecode->weather[0]->icon;
		$urlIcon = "http://openweathermap.org/img/w/".$icon.".png";
		$temp = $meteoDecode->main->temp;
		$description = $meteoDecode->weather[0]->description;
		
		$html = $html.<<<EOD
	
		<section>
		<iframe style="border: none;box-shadow: 1px 1px 3px black;float: left; margin: 0 2em 2em 0;width:600px; height:480px;"
			src="http://www.openstreetmap.org/export/embed.html?bbox=$boundingbox[2]%2C$boundingbox[0]%2C$boundingbox[3]%2C$boundingbox[1]&amp;layer=mapnik"></iframe>
		<p>Le temps à $nom : </p>
		<img src="$urlIcon">
		<p>Température de $temp °C, $description</p>
		</section>
		
		EOD;
		
	}
	
?>
<!doctype html>
<html lang="fr">
<head>
  <meta charset="utf-8">
	<style type="text/css">
		section {
				width: 200px;
			}
	</style>
  <title>Météo</title>
  <!-- licence Creative Commons Attribution-ShareAlike (CC-BY-SA) -->
  <!-- API OpenWeather : 1dc250956d9b1464e48dd58f63d25cfb -->
</head>
<body>
	<section id="formulaire">
		<h1>Formulaire</h1>
	<form action="" method="get">
	<label for="adresse">Entrez une adresse : </label>
    <input type="text" name="adresse" id="adresse" required>
	</form>
	</section>
	<br>
	
	<?php echo $html ?>
	
</body>
</html>