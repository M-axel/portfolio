<?php

unset($_GET['action']);
unset($_SESSION["grille_resultat"]);
unset($_SESSION["grille_reponses"]);
unset($_SESSION["reponses_utilisees"]);
unset($_SESSION["questionRestantes"]);
unset($_SESSION["nb_coups"]);
unset($_GET['case']);


header("Location: index.php"); //Pour enlever le "?action=recommencer"

?>