Arquivo de configuração de cena: scene.txt no diretório anterior ao projeto

Parâmetros:

obj <nome do arquivo>: nome do arquivo no diretório objs*
pos <x> <y> <z>: posição na cena do último obj informado
scale <scale>: valor de escala do último obj informado (padrão se não informado é 1.0)
rot <coord> <angulo>: ângulo de rotação do último obj informado e vetor a ser rotacionado (se x (1, 0, 0), se y (0, 1, 0) ou se z (0, 0, 1))
anim <x1> <y1> <x2> <y2> <x3> <y3> <x4> <y4>: trajetória da primeira animação utilizando curva de bezier (4 pontos de controle 2d)
anim <x1> <y1> <x2> <y2> <x3> <y3> <x4> <y4>: trajetória da segunda animação utilizando curva de bezier (4 pontos de controle 2d)
cam <x> <y> <z>: posição inicial da câmera
lightpos <x> <y> <z>: posição da fonte de iluminação
lightamb <x> <y> <z>: intensidade da iluminação ambiente
lightdif <x> <y> <z>: intensidade da iluminação difusa
lightspec <x> <y> <z>: intensidade da iluminação especular
coefspec <n>: coeficiente da especular
bgcolor <r> <g> <b>: cor de fundo da cena
 
* se houver, arquivo .mtl e imagens de textura devem estar localizados no mesmo diretório do obj

Controles:

ESC: Fecha a janela

A: translação para a esquerda em relação a posição da câmera
D: translação para a direita em relação a posição da câmera
W: desloca a câmera para frente
S: desloca a câmera para trás

Scroll do mouse controla o deslocamento frente/trás da câmera

Mouse controla a direção da câmera