<?php  
	
	//Traitement de la réponse contenue dans ?case=...
	
	if((isset($_GET['case']) && ($_SESSION['etat'] != 'jeu-fini'))){
		if(!isset($_SESSION["nb_coups"])){$_SESSION["nb_coups"]=0;}
		$_SESSION["nb_coups"] = $_SESSION["nb_coups"] + 1;
		$_SESSION['NbTotalCoup'] = $_SESSION['NbTotalCoup'] + 1;
		$reponse = $_GET['case'];
		$reponse = intval($reponse);

			if($reponse >= 1 && $reponse <= $_SESSION["taille"]){		
				if(isset($_SESSION["question_courante"])){
					if( $reponse == $_SESSION["grille_resultat"][$_SESSION["question_courante"]]){		//Bonne réponse
						$_SESSION["grille_reponses"][$_SESSION["question_courante"]] = true;	//Pas question_courante -1 ?
						$_SESSION["reponses_utilisees"][$_SESSION["question_courante"]] = true;
						unset($_SESSION["question_courante"]);
						
						//Fin de partie ? Toutes les valeurs de $_SESSION["reponses_utilisees"] sont true ?
						//Nombre de true == nombre de question ?
						if(array_sum($_SESSION["reponses_utilisees"]) == $_SESSION["taille"]){
							
							if( (!isset($_SESSION["nb_coups_max"])) || ($_SESSION["nb_coups"] > $_SESSION["nb_coups_max"]) ){
								$_SESSION["nb_coups_max"] = $_SESSION["nb_coups"];
							}
						
							if( (!isset($_SESSION["nb_coups_min"])) || ($_SESSION["nb_coups"] < $_SESSION["nb_coups_min"]) ){
								$_SESSION["nb_coups_min"] = $_SESSION["nb_coups"];
							}
							
							$_SESSION['etat'] = 'jeu-fini';
						}
					}
				}
			}
	}
	
	//On selectionne une case à deviner
	
	 //On genere une liste aléatoire qui sera l'ordre dans lequel seront demandé les cases de la grille
	if(!isset($_SESSION["questionRestantes"])){
	$_SESSION["questionRestantes"] = array();
	for($i = 1; $i <= $_SESSION["taille"]; $i++){
			array_push($_SESSION["questionRestantes"], $i);
		}
		shuffle($_SESSION["questionRestantes"]);
		}
		
	/*On vérifie que question courante ne soit pas changée si elle n'a pas été trouvée !
	grilleReponse[questionActuelle] renvoit false si la question n'a pas été répondu.
	Le if peut tomber sur (true && 3) => TRUE ! Pas de problème
	*/
	if(isset($_SESSION["question_courante"]) && $_SESSION["grille_reponses"][$_SESSION["question_courante"]]){
	$_SESSION["question_courante"] = array_pop($_SESSION["questionRestantes"]); //On prends le dernier element et on l'enlève
	}
	else if(!isset($_SESSION["question_courante"])){
		$_SESSION["question_courante"] = array_pop($_SESSION["questionRestantes"]);
	}	
	
	//Génération du html
	
	//Génération du bandeaux de réponse
	if($_SESSION["etat"] != 'jeu-fini'){
	$html = '<h2>Quel est le numéro correspondant à la case surlignée ?</h2><header><nav>';}
	else{
	$html="<h2>Bravo, vous les avez toutes retrouvées en ".$_SESSION["nb_coups"]." coups</h2><br><header><nav>";}
	
	$ligneOrdonne = array();
	foreach($_SESSION["reponses_utilisees"] as $key => $value){
		$ligneOrdonne[$_SESSION["grille_resultat"][$key]] = $value;
	}
	
	ksort($ligneOrdonne);
	
	foreach($ligneOrdonne as $key => $value){
		if(!$value){
			$html = $html.'<span id="'.$key.'"onclick="AToSpan('.$key.')"><a href="?action=commencer&case='.$key.'">'.$key.'</a></span>';}
		else{ $html = $html.'<span id="'.$key.'" class="disabled">'.$key.'</span>';}
	}	
	
	$html= $html.'</header></nav>';
	
	$html = $html.'<section id="grille">';
	
	for($i = 1; $i <= $_SESSION["taille"]; $i++){
		if (($_SESSION["grille_reponses"][$i] == false) && ($i == $_SESSION["question_courante"])){
		$html = $html.'<span class="tofind" id="i'.$i.'"></span>';
		}
		else if($_SESSION["grille_reponses"][$i] != false){
			$html = $html.'<span class= "founded" id="i'.$i.'">'.$_SESSION["grille_resultat"][$i].'</span>';		}
		else{
			$html = $html.'<span class="notfounded" id="i'.$i.'"></span>';
		}
		
	}
	
	$html = $html.'</section>';
	
	$html = $html.'<section id="menu"><span>';
	if($_SESSION['etat'] == 'jeu-fini'){
		$html = $html."Vous avez terminez la grille, vous avez mis ".$_SESSION["nb_coups"]." essaies sur ".$_SESSION["taille"].' minimum. Vous pouvez <a href="?action=recommencer">recommencer maintenant</a>.';
	}
	else {
		$html = $html."Cliquez sur le nombre au dessus de la grille correspondant à la case mise en valeur";
	}
	
	$html = $html.<<<EOD
	<br><br>
				<a href="?action=abandon">Recommencer à zéro (abandon définitif de la partie en cours)</a>
			</span>
		</section>
	EOD;
	
?>

	<?php echo $html; ?>
