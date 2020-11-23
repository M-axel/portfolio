##### Auteur : Axel MAISSA #####
######### N°: 21711378 #########

from math import *
from random import randint

noir = color(0, 0, 0)
blanc = color(255, 255, 255)
bleu = color(0,0,255)
jaune = color(255,255,0)

def setup() :
    global t, xpos, ypos, xvit, yvit,L,H,c,dir, score
    size(800, 550)
    xpos = 400
    ypos = 275   #Position de départ
    xvit = 0     #Vitesse de départ
    yvit = 0
    dir = 'r'    #La direction de départ sera right
    score = 0
    
    SetupGomme(5)  #Nombre de Gomme
    
    ellipseMode(CENTER)
    frameRate(28)
    t = 0
    background(noir)
    fill(noir)
    
    
    
def draw():  
    global t, xpos, ypos, xvit, yvit,L,H,c
    
    c = 20*sin(t * PI/6)
    macman(20*sin(t * PI/6),xpos,ypos)
    
    MacGomme() 
    Compteur()
    
    (t,xpos,ypos,xvit,yvit) = suivant(t,xpos,ypos,xvit,yvit)  #Permet de passer au 'monde' suivant
    
    
def suivant(t,xpos,ypos,xvit,yvit):
    global dir                    #Pour pouvoir changer la direction de la bouche en cas de rebond
    global lxPos,lyPos,score   
    xpos2 = xpos + xvit
    ypos2 = ypos + yvit

                                  #60 = espace entre bord et mur du plateau 
    if xpos2 < 60 or xpos2 > 760 - 25 :   
        xvit = - xvit
        if dir == 'r':
            dir = 'l'             #Si collision, renvoyer la direction de la bouche opposée 
        elif dir == 'l':
            dir = 'r'
    elif ypos2 < 60 or ypos2 > 510 - 25 : 
        yvit = - yvit             #Si ces limites sont dépassées : vitesse dans le sens opposé
        if dir == 'u':
            dir = 'd'      
        elif dir == 'd':
            dir = 'u'
    elif xpos2 > 375 and xpos2 < 425 and ypos2 < 70 :      #Si MacMan atteint la porte du haut, le renvoyer en bas
        ypos = 479
    elif xpos2 > 375 and xpos2 < 425 and ypos2 > 480 :      #Si MacMan atteint la porte du bas, le renvoyer en haut
        ypos = 71                                           #479 et 71 pour eviter les téléportation à l'infini, je pourais aussi mettre en condition le signe de yvit
    elif ypos2 > 240 and ypos2 < 295 and xpos2 < 65 :       #Si MacMan atteint la porte gauche, le renvoyer à droite
        xpos = 720
    elif ypos2 > 240 and ypos2 < 295 and xpos2 > 730 :  
        xpos = 66
    else :
        (xpos, ypos) = (xpos2, ypos2)
    
    for i in range (len(lxPos)):                            #On vérifie si MacMan s'approche d'une Gomme
        if (lxPos[i]+15 > xpos and lxPos[i] - 15 <xpos) and (lyPos[i]+15 > ypos and lyPos[i] - 15 < ypos) :
            lxPos[i] = -10                                   #Quand une gomme est touché, elle sort de l'écran (pas très élégant)
            lyPos[i] = -10
            score += 1                                      #On ajoute un point
            
    return (t+1, xpos, ypos, xvit, yvit)                    #On incrémente le temps

def plateau() :    
    background(noir)
    rectMode(CORNER)
    stroke(bleu)
    strokeWeight(2)
    
    #Murs gauche
    rect(30,30,0,220)  
    rect(40,40,0,210)  #Mur gauche, haut
    
    rect(30,300,0,220)
    rect(40,300,0,210)  #Mur gauche bas
    
    #Mur haut
    rect(30,30,340,0)
    rect(40,40,330,0)  #Mur haut gauche
    
    rect(420,30,340,0)  #Mur haut droit
    rect(420,40,330,0)
    
    #Murs droit
    rect(760,30,0,220)  
    rect(750,40,0,210)  #Mur droit, haut
    
    rect(760,300,0,220)
    rect(750,300,0,210)  #Mur droit bas
    
    #Mur bas
    rect(30,520,340,0)
    rect(40,510,330,0)  #Mur bas gauche
    
    rect(420,520,340,0)  #Mur bas droit
    rect(420,510,330,0)
    
def macman(c,xpos,ypos):
    global dir
    plateau()  #Permet d'afficher le plateau à chaque frame pour ne pas avoir de trace
    
    #Corps de Mac-man
    color(jaune)
    stroke(jaune)
    fill(jaune)
    ellipse(xpos,ypos,35,35)
    
    #Bouche de Mac-man
    fill(noir)
    stroke(noir)
    
    #V2 avec bouche triangle
    fill(noir)
    strokeWeight(0)
    
    if dir == 'r' :   #Permet de modifier la direction de la bouche en fonction de keypressed 
        triangle(xpos,ypos,xpos+20,ypos-10+c,xpos+20,ypos+10-c) 
    elif dir == 'u' :
        triangle(xpos,ypos,xpos-c,ypos-20,xpos+c,ypos-20)
    elif dir == 'l' :
        triangle(xpos,ypos,xpos-20,ypos-10+c,xpos-20,ypos+10-c)
    elif dir == 'd' :
        triangle(xpos,ypos,xpos-c,ypos+20,xpos+c,ypos+20)
    
def keyPressed():
    global xpos, ypos,xvit,yvit
    global dir   #Sert à donner la direction de la bouche
    vit = 5
    xvit = 0    #On réinitialise les vitesses dès qu'une nouvelle commande est donnée
    yvit = 0    #Pour que on ne puisse pas le faire aller plus vite
    if key == CODED :
        if keyCode == LEFT :
            xvit -= vit
            dir = 'l'    # On change la direction de la bouche
        elif keyCode == RIGHT :
            xvit += vit
            dir = 'r'
        elif keyCode == UP :
            yvit -= vit
            dir = 'u'
        elif keyCode == DOWN :
            yvit += vit
            dir = 'd'
            

def SetupGomme(n):  #Créer les coordonnées des Gommes mais ne doit pas être répété
    global lxPos,lyPos
    lxPos = []   #On enregistre la position x des gommes
    lyPos = []
    
    xpos = 40
    ypos = 30
    
    for i in range(n) :
        ellipse(xpos,ypos,15,15)
        xpos = xpos + randint(20,250)    #A chaque nouveau jeu, les gommes sont placées aléatoirement
        ypos = ypos + randint(10,190)
        lxPos.append(xpos)
        lyPos.append(ypos)  #Pour retenir les positions puisque ce for se fera une unique fois
        i += 1
        
def MacGomme():
    global lxPos,lyPos   #Listes de coordonées
    
    fill(blanc)
    ellipseMode(CENTER)

    for i in range (5):
        ellipse(lxPos[i],lyPos[i],15,15)  #Dessine les gommes avec les listes de coordonées
        
def Compteur():   #Compteur de point
    global score
    
    textSize(15)
    fill(blanc)
    text('Score :', 25, 20)
    text(score, 80,20)
    
