#Alunos: Anderson Caique de Sousa, Lucas Santos de Almeida, Renato Kajiwara
#! /usr/bin/env python
import pygame,sys
from pygame.locals import *
from sys import exit
from random import randrange

pygame.init()
pygame.font.init()

#inicializa o módulo de fontes do Pygame
font_name = pygame.font.get_default_font()
game_font = pygame.font.SysFont(font_name, 72)

font = pygame.font.SysFont('Calibri', 25, True, False)


#Musica
music = pygame.mixer.music.load ("music/blassic.ogg")
pygame.mixer.music.play(-1)

#inicializa a tela e os parametros
preto = (0, 0, 0)
branco = (255,255,255)
BLUE = (0, 0, 255)
RED = (255, 0, 0)

ecra = pygame.display.set_mode((800, 600), 0, 32)

#declara o tempo e o vetor asteroides
tempo_asteroid = 15
asteroids = []
score = 0
angulo = 0
tiros = []
#float = angulo

# calcula o FPS e o delay
# se queremos 20 FPS, calcula delay = 1000 / 20 = 50 millisegundos
delay = 30; 
t1 = pygame.time.get_ticks()



#registro nave
nave = {
    'img': pygame.image.load('img/player.png').convert_alpha(),
    'move': [randrange(800), (550)],
    'vida': 0,
    'angulo': 0,
    'vel': {
        'x': 1,
        'y': 1
        
    }
}

#registro tiro
tiro = {
    'img':pygame.image.load('img/bullet.png').convert_alpha(),
    'move':[randrange(800), (550)],
    'angulo':0,
    'vel': {
        'x': 1,
        'y': 1
    }
}

#registro de destruição da nave
explo_nave = {
    'img': pygame.image.load('img/ship_exploded.png').convert_alpha(),
    'move': [],
    'vel': {
        'x': 0,
        'y': 0
    },
    'rect': Rect(0, 0, 48, 48)
}



def update(self):
        self.rect.bottom += self.dy
        if self.rect.bottom >= 1200:
            self.reset()
            
            
#cria a variavel de colisão e inicia ela com False
crash = False

#Nome no topo da tela
pygame.display.set_caption(' ================== "Chuva de Asteroides" ==================')


#função asteroides
def listaAsteroide():
    return {
        'img': pygame.image.load('img/asteroids.png').convert_alpha(),
        'pontos': 10,
        'move': [randrange(805), 0],
        'vel': randrange(1, 11)
    }


#função que move os asteroides
def move_asteroids():
    for asteroid in asteroids:
        asteroid['move'][1] += asteroid['vel']

#função que remove os astroides
def remove_asteroids():
    for asteroid in asteroids:
        if asteroid['move'][1] > 550:
            asteroids.remove(asteroid)

#cria um objeto rect, para ajudar na colição, pega os parametros do retangulo da img e assim fzer a animaçao de destruicao
def rect(obj):
    return Rect(obj['move'][0],
                obj['move'][1],
                obj['img'].get_width(),
                obj['img'].get_height())

#retangulo para o tiro
def rect2(obj):
    return Rect2(obj['move'][0],
                obj['move'][1],
                obj['img'].get_width(),
                obj['img'].get_height())


#função que detecta colição
def nave_colidiu():
    nave_rect = rect(nave)
    for asteroid in asteroids:
        if nave_rect.colliderect(rect(asteroid)):
            return True
    return False

colidiu = False
animacao_colisao = 0
################################################################################
#MENU
#carrega as imagens de botao iniciar e sair
p1 = pygame.image.load('img/iniciar.png') 
ex = pygame.image.load('img/sair.png')
# carrega background
bg = pygame.image.load('img/Fundo.jpg')
#carrega logo
logo = pygame.image.load('img/logo.png')

ecra.blit( bg, (0,0)) #coloca a background na tela
ecra.blit( logo, (150,20)) #coloca a logo na tela
ecra.blit( p1, (240,300)) #coloca a iniciar na tela
ecra.blit( ex, (240,350)) #coloca a sair na tela
pygame.display.flip() # atualiza a surface

MenuAtivo = True
while MenuAtivo:
#trata os eventos da fila de eventos
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
            MenuAtivo = False
        if event.type == KEYDOWN:
            print('uma tecla foi pressionada')
            #entrada no jogo
            if event.key == pygame.K_SPACE:
                print("Entrei no jogo")
                MenuAtivo = False
                JogoAtivo = True

################################################################################

#cria os asteroides em 15 milesegundos
while JogoAtivo:

    if not tempo_asteroid:
        tempo_asteroid = 15
        asteroids.append(listaAsteroide())
    else:
        tempo_asteroid -= 1

    nave['vel'] = {
        'x': 0,
        'y': 0
    }
 

    
#simulação do jogo
    gira = True
    for event in pygame.event.get():
        if event.type == QUIT:
            done = True
            
        

    
    pressed_keys = pygame.key.get_pressed()

    if pressed_keys[K_UP]:
        #angulo+=nave['vel']['x'],nave['vel']['y']/2
        nave['vel']['y']-=5
        #nave['vel']['y'] = -5
        
    elif pressed_keys[K_DOWN]:
        nave['vel']['y'] = 5

    if pressed_keys[K_LEFT]:
        nave['vel']['x'] = -5
        #angulo+=5;
        #naveGirada = pygame.transform.rotate(nave['img'], angulo)
        
    elif pressed_keys[K_RIGHT]:
        nave['vel']['x'] = 5
        #angulo-=5
        #naveGirada = pygame.transform.rotate(nave['img'], angulo)

    if pressed_keys[K_1]:
        tiro['move']['y']-= 3
        tiro['move']['x'] = nave['move']['x']
        tiro['move']['y'] = nave['move']['y']
        #tiros.append(tiro())
        print("atiro")

    #Gravidade    
    if pressed_keys:
       #nave['vel']['x']+=1
       #nave['vel']['y']-=1

       def update(self):
        self.rect.move_ip((self.dx, self.dy))
        
        #Fire the laser
  
         
    
    #teste usando mouse   
    #nave['vel']['x'],nave['vel']['y'] = pygame.mouse.get_rel()
    
       


    #if gira:
      #  angulo+=30;
      # naveGirada = pygame.transform.rotate(nave['img'], angulo)
    

#blits e updates       

    ecra.fill(preto)

    move_asteroids()
    
    for asteroid in asteroids:
       ecra.blit(asteroid['img'], asteroid['move'])
       

    naveGirada = pygame.transform.rotate(nave['img'], angulo)   
    #verifica colisão
    if not colidiu:
        colidiu = nave_colidiu()
        nave['move'][0] += nave['vel']['x']
        nave['move'][1] += nave['vel']['y']
        placar = font.render("Placar: " + str(score), 1, (0, 255, 255))
        ecra.blit(naveGirada, nave['move'])
    else:
        if not crash:
            crash = True
            nave['move'][0] += nave['vel']['x']
            nave['move'][1] += nave['vel']['y']

            ecra.blit(nave['img'], nave['move'])
        elif animacao_colisao == 3:
            text = game_font.render('GAME OVER', 1, (255, 0, 0))
            ecra.blit(text, (250, 250))
        else:
            explo_nave['rect'].x = animacao_colisao * 48
            explo_nave['move'] = nave['move']
            ecra.blit(explo_nave['img'], explo_nave['move'],
                        explo_nave['rect'])
            animacao_colisao += 1
    
    ecra.blit(placar, (0, 0))
    ecra.blit(tiro['img'], tiro['move'])
            
    #update da tela
    pygame.display.update()
    # FPS - calcula os milissegundos passados
    t2 = pygame.time.get_ticks() - t1;
    if t2 < delay:
        # espera o resto do tempo
        pygame.time.delay(delay - t2);
    
    #atualiza t1
    t1 = pygame.time.get_ticks()

    remove_asteroids()
