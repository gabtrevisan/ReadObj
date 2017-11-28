Arquivo de configura��o de cena: scene.txt no diret�rio anterior ao projeto

Par�metros:

obj <nome do arquivo>: nome do arquivo no diret�rio objs*
pos <x> <y> <z>: posi��o na cena do �ltimo obj informado
scale <scale>: valor de escala do �ltimo obj informado (padr�o se n�o informado � 1.0)
rot <coord> <angulo>: �ngulo de rota��o do �ltimo obj informado e vetor a ser rotacionado (se x (1, 0, 0), se y (0, 1, 0) ou se z (0, 0, 1))
cam <x> <y> <z>: posi��o inicial da c�mera
light <x> <y> <z>: posi��o da fonte de ilumina��o
 
* se houver, arquivo .mtl deve estar localizado no mesmo diret�rio do obj

C�mera controlada apenas por teclado, com ilumina��o est�tica.

Controles:

ESC: Fecha janela

LEFT: Move a c�mera no eixo X (esquerda)
RIGHT: Move a c�mera no eixo X (direita)
UP: Move a c�mera no eixo Y (cima)
DOWN: Move a c�mera no eixo Y (baixo)
+: Move a c�mera no eixo Z (frente)
-: Move a c�mera no eixo Z (tr�s)