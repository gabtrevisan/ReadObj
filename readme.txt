Arquivo de configura��o de cena: scene.txt no diret�rio anterior ao projeto

Par�metros:

obj <nome do arquivo>: nome do arquivo no diret�rio objs*
pos <x> <y> <z>: posi��o na cena do �ltimo obj informado
scale <scale>: valor de escala do �ltimo obj informado (padr�o se n�o informado � 1.0)
rot <coord> <angulo>: �ngulo de rota��o do �ltimo obj informado e vetor a ser rotacionado (se x (1, 0, 0), se y (0, 1, 0) ou se z (0, 0, 1))
cam <x> <y> <z>: posi��o inicial da c�mera
lightpos <x> <y> <z>: posi��o da fonte de ilumina��o
lightamb <x> <y> <z>: intensidade da ilumina��o ambiente
lightdif <x> <y> <z>: intensidade da ilumina��o difusa
lightspec <x> <y> <z>: intensidade da ilumina��o especular
bgcolor <r> <g> <b>: cor de fundo da cena
 
* se houver, arquivo .mtl e imagens de textura devem estar localizados no mesmo diret�rio do obj

C�mera controlada apenas por teclado

Controles:

ESC: Fecha janela

LEFT: Move a c�mera no eixo X (esquerda)
RIGHT: Move a c�mera no eixo X (direita)
UP: Move a c�mera no eixo Y (cima)
DOWN: Move a c�mera no eixo Y (baixo)
+: Move a c�mera no eixo Z (frente)
-: Move a c�mera no eixo Z (tr�s)