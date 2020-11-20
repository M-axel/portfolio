<?php

// il faut détruire la session : copier coller de php.net...
// Initialisation de la session. 
// Si vous utilisez un autre nom : session_name("nom de la session") 
session_start(); 

// Détruit toutes les variables de session 
$_SESSION = array(); 
/* Si vous voulez détruire complètement la session, effacez également le cookie de session. cela détruira la session et pas seulement les données de session ! */
if (isset($_COOKIE[session_name()]))  {
	 setcookie(session_name(), '', time()-42000, '/'); 
} 

// Finalement, on détruit la session. 
session_destroy();

// selon la position du code, redirection ou non
header("Location: index.php");
return; // sécurité

?>