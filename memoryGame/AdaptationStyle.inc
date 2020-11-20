<?php 
	$taille = $_SESSION["taille"];
	$sqrt = sqrt($taille);
	
	$css = "#grille span{flex-basis: calc(96% /".$sqrt."); height:calc(96% /".$sqrt.");";
	
	$css = $css.<<<EOD
	/* A cahnger en fonction du nombre de cases. Pourquoi 96 ? Car 33% fait revenir à la ligne la dernière case de la ligne */
	border:1px solid;
	border-color:black;
	display: flex;
	align-items: center;
	justify-content: center;
	box-shadow: 2px 2px 2px 2px #aaa;
	}
	EOD;
	
	//Calcul du num de la case inferieure bas
	$child = $taille + 1 - $sqrt;
	$css = $css."#grille :nth-child(1){border-top-left-radius: 5px;}";
	$css = $css."#grille :nth-child(".$sqrt."){border-top-right-radius: 5px;}";
	$css = $css."#grille :nth-child(".$child."){border-bottom-left-radius: 5px;}";
	$css = $css."#grille :nth-child(".$taille."){border-bottom-right-radius: 5px;}";
	
	$dim = 50*$sqrt;
	
	
	$css = $css."#grille{
	display: flex;
	flex-wrap: wrap;
	height: ".$dim."px;
	width: ".$dim."px;
	margin: 50px;
}";
	
	
	
	
	echo $css;
?>