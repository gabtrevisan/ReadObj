Arquivo de configuração de cena: scene.txt no diretório anterior ao projeto

Parâmetros:

obj <nome do arquivo>: nome do arquivo no diretório objs*
pos <x> <y> <z>: posição na cena do último obj informado
scale <scale>: valor de escala do último obj informado (padrão se não informado é 1.0)
rot <coord> <angulo>: ângulo de rotação do último obj informado e vetor a ser rotacionado (se x (1, 0, 0), se y (0, 1, 0) ou se z (0, 0, 1))
cam <x> <y> <z>: posição inicial da câmera
light <x> <y> <z>: posição da fonte de iluminação
bgcolor <r> <g> <b>: cor de fundo da cena
 
* se houver, arquivo .mtl e imagens de textura devem estar localizados no mesmo diretório do obj

Câmera controlada apenas por teclado

Controles:

ESC: Fecha janela

LEFT: Move a câmera no eixo X (esquerda)
RIGHT: Move a câmera no eixo X (direita)
UP: Move a câmera no eixo Y (cima)
DOWN: Move a câmera no eixo Y (baixo)
+: Move a câmera no eixo Z (frente)
-: Move a câmera no eixo Z (trás)