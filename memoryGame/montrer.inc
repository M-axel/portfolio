<?php
	$taille = $_SESSION["taille"];
	
	/*Generation de la grille à trouver*/
	if(!isset($_SESSION["grille_resultat"])){
		$grille = array();
		/*Creer un array avec des elements distincts de 1 à $taille*/
		for($i = 1; $i <= $taille; $i++){
			array_push($grille, $i);
		}
		
		/*Puis on mélange l'ordre*/
		shuffle($grille);
		
		
		/*$random = rand(1,9);
		for($i = 1; $i <= $taille; $i++){On boucle sur les indices (de 1 à $taille)
			foreach($grille as $case){	On boucle une seconde fois sur la grille cette fois pour vérifier que notre random n'a pas déjà était rentré dans la grille
				while($case == $random){ Tant que le random n'est pas différents de 													toute les cases déjà remplie
					$random = rand(1,9);
				}
			}
			
			$grille[$i] = $random;
			
		}*/
		
		$_SESSION["grille_resultat"] = $grille; /*Je n'ai pas directement modifié la 			variable session pour ne pas l'appeler trop souvent*/
		for($j = 1; $j <= $taille; $j++){
			$_SESSION["grille_resultat"][$j] = $grille[$j-1];
			// Permet de rétablir le décallage d'indice ($grille commence à 0)
		}
	}
	
	//conteneur des réponses trouvées (pour l'instant, false de partout (false = pas trouvé)
	for($i = 1; $i <= $_SESSION["taille"]; $i++){
		$_SESSION["grille_reponses"][$i] = false;
	}

	//Generation du tableau des réponses (utilisé true) et non-utilisé (false)

	for($j = 1; $j <= $_SESSION["taille"]; $j++){
			$_SESSION["reponses_utilisees"][$j] = false;
		}
	
	/*Création de la grille avec l'array $_SESSION["grille_resultat"]*/
	$html = '<h1>Mémorisez le tableau :</h1><section id="grille">';
	for($i = 1; $i <= $taille; $i++){  //On aura l'indice de la première case = 0 et non 1
		$html = $html.'<span id="i'.$i.'">'.$_SESSION["grille_resultat"][$i].'</span>';
	}
	$html = $html."</section>";
	
	/*Ajout de l'encart menu*/
	
	$html = $html.<<<EOD
		<section id="menu">
			<span>
				<a href="?action=commencer">Commencez le jeu</a>
				<br><br>
				<a href="?action=abandon">Recommencez à zéro</a>
			</span>
		</section>
	EOD;	
?>

	<?php echo $html; ?>
