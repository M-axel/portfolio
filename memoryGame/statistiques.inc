<?php
	
	if(!isset($_SESSION['NbTotalCoup'])){$_SESSION['NbTotalCoup'] = 0; }
	if(!isset($_SESSION['NbPartie'])){$_SESSION['NbPartie'] = 0; }
	
	
	$stats = '<section id="stats"><h3>Statistiques</h3><br><span>Vous avez joué '.$_SESSION['NbPartie'].' partie(s)</span><br/><span>Nombre total de coups : '.$_SESSION['NbTotalCoup'];
	
	if(isset($_SESSION["nb_coups_min"]) && isset($_SESSION["nb_coups_max"])){
	$stats = $stats.' <br>Votre nombre d\'essaies minimum pour finir une partie est de '.$_SESSION["nb_coups_min"].' coups, le nombre d\'essaies maximum est de '.$_SESSION["nb_coups_max"].' coups.</span></section>';
	}
	echo $stats;
?>