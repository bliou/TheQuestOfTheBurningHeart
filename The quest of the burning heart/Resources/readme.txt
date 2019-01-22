Pour cr�er sa propre carte, il faut cr�er deux fichiers :
- mapx.txt dans Maps
- mapx.json dans Tiles

Dans le fichier mapx.txt, il faudra repr�senter la carte � l'aide de :
- xxx (vide)
- txx : une tile, les tiles sont num�rot�es comme suit:
	- t0x: Les tiles basiques
	- t1x: Les tiles mobiles
	- t2x: Les tiles qui tombent
	- t3x: Les tiles bonus
	- t4x: Les tiles �l�mentaires (change la couleur du joueur)
	- t5x: Les tiles de changement de niveau
- cxx: un personnage qui sont num�rot�s comme suit:
	- c00: Player
	- c10: Un pigeon blanc
	- c11: Un pigeon rouge

Dans le fichier mapx.json, il faudra choisir les caract�ristiques des tiles:
- id: l'id de la tile. Ex: t10 -> id = 10
- spritePosition: la position du sprite dans la texture
- minPosition: la position minimal de la tile (Seulement les tiles mobiles)
- maxPosition: la position maximal de la tile (Seulement les tiles mobiles)
- tick: nombre de tick pour parcourir la distance (Seulement les tiles mobiles)
- fallTimeout: Le d�lai avant l'effondrement de la tile (Seulement les tiles tombantes)
- type: Le type de bonus a gagn� (Seulement les tiles bonus)
- color: La couleur a donn� au jouer (Seulement les tiles �l�mentaires)
- nextLevel: Le niveau suivant auquel conduit cette tile (Seulement les tiles de fin)
