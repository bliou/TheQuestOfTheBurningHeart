Pour créer sa propre carte, il faut créer deux fichiers :
- mapx.txt dans Maps
- mapx.json dans Tiles

Dans le fichier mapx.txt, il faudra représenter la carte à l'aide de :
- xxx (vide)
- txx : une tile, les tiles sont numérotées comme suit:
	- t0x: Les tiles basiques
	- t1x: Les tiles mobiles
	- t2x: Les tiles qui tombent
	- t3x: Les tiles bonus
	- t4x: Les tiles élémentaires (change la couleur du joueur)
	- t5x: Les tiles de changement de niveau
- cxx: un personnage qui sont numérotés comme suit:
	- c00: Player
	- c10: Un pigeon blanc
	- c11: Un pigeon rouge

Dans le fichier mapx.json, il faudra choisir les caractéristiques des tiles:
- id: l'id de la tile. Ex: t10 -> id = 10
- spritePosition: la position du sprite dans la texture
- minPosition: la position minimal de la tile (Seulement les tiles mobiles)
- maxPosition: la position maximal de la tile (Seulement les tiles mobiles)
- tick: nombre de tick pour parcourir la distance (Seulement les tiles mobiles)
- fallTimeout: Le délai avant l'effondrement de la tile (Seulement les tiles tombantes)
- type: Le type de bonus a gagné (Seulement les tiles bonus)
- color: La couleur a donné au jouer (Seulement les tiles élémentaires)
- nextLevel: Le niveau suivant auquel conduit cette tile (Seulement les tiles de fin)
