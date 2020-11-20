<?php
include "session.inc";

$_SESSION["taille"] = 9; //C'est ici qu'on modifie la taille

if(!isset($_SESSION['etat'])){
	$_SESSION['etat'] = 'initial';
}

if(isset($_GET['action'])){
	$action = $_GET['action'];;
}
else{$action = '';}//Pas terrible de faire ça mais sinon on a des messages d'erreur

if( $action == 'abandon'){echo include "deconnexion.inc";} /*Remise à zero en appelant la fonction JS*/
else if( $action == 'recommencer'){
	$_SESSION['NbPartie'] = $_SESSION['NbPartie'] + 1;
	include "reinitialisation.inc";
	$_SESSION['etat'] = 'debut-partie'; 
	}
else if($_SESSION['etat'] == 'jeu-fini'){} //Pour casser le elseif d'après 
else if( $action == 'commencer'){$_SESSION['etat'] = 'en-jeu';}
else{ $_SESSION['etat'] = 'initial'; }


/*  Pour vérifier toutes les variables pendant le développement :
echo "Action :".$action;
echo "<br>Etat : ".$_SESSION['etat'];
echo "<br>Grille resultat : ";
foreach($_SESSION["grille_resultat"] as $res){
	echo $res." ";}
echo "et le l'indice 0 donne".$_SESSION["grille_resultat"][2];
echo "<br>Reponses déjà trouvées (F = pas trouvé) : ";
foreach($_SESSION["grille_reponses"] as $res){
	if($res){ echo "T ";}
	else{echo "F ";}
	}
echo "<br>Réponses déjà données(utilisées), ordre des chiffres 1-2-3... : ";
foreach($_SESSION["reponses_utilisees"] as $key => $value){
	echo ' '.$key.':';
	if($value){ echo "T ";}
	else{echo "F ";}
	}
echo "<br>Question courante : ".$_SESSION["question_courante"];
echo "<br>Questions restantes : ";
foreach($_SESSION["questionRestantes"] as $res){
	echo $res." ";
	}
*/

?>

<!doctype html>
<html lang="fr">
<head>
  <meta charset="utf-8">
  <title>Titre de la page</title>
  <link rel="stylesheet" href="style.css">
	<script type="text/javascript" src="script.js"></script>
	<style><?php include "AdaptationStyle.inc"; ?></style>
</head>
<body>
	  <?php 
	  		if( $_SESSION['etat'] == 'initial' || $_SESSION['etat'] == 'debut-partie'){
			include('montrer.inc');}
			else if( $_SESSION['etat'] == 'en-jeu' || $_SESSION['etat'] == 'jeu-fini' ){
			include('question.inc');}
			
			include('statistiques.inc');
?>	
</body>
</html>