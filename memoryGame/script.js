function AToSpan(id)
{
	document.getElementById(id).innerHTML = id; 
	document.getElementById(id).setAttribute("class","disabled");
	}
	
	
/** destruction de la session **/
function detruireSession() {
/* il faut detruire la session : copier coller de php.net...
/ La session est deja initialisee
/ Detruit toutes les variables de session */
	$_SESSION = array();
/* Si vous voulez detruire completement la session, effacez egalement
/ le cookie de session.
/ cela detruira la session et pas seulement les donnees de session !*/
if (isset($_COOKIE[session_name()])) { setcookie(session_name(), '', time()-42000, '/');
}
/* Finalement, on detruit la session. session_destroy();
/ on termine par la redirection*/
header("Location: index.php"); 
}