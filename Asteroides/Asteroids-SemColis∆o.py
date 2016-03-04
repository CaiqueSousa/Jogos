#Alunos: Anderson Caique de Sousa, Lucas Santos de Almeida, Renato Kajiwara
import pygame,sys
import random
from pygame.locals import *
from sys import exit
from random import randrange
 
#Cores
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
BLUE = (0, 0, 255)
RED = (255, 0, 0)

#FINAL

#Classes
 
class Player(pygame.sprite.Sprite):
 
    def __init__(self):
        #Chamar o construtor da classe(Sprite)
        super().__init__()
 
        self.image = pygame.image.load('img/player.png')
 
        self.rect = self.image.get_rect()

    #controle de mouse
    def update(self):
        #Update da posiçao do player
        
        self.rect.x,self.rect.y = pygame.mouse.get_pos()
        self.rect.x -= self.image.get_width()/2
        self.rect.y -= self.image.get_height()/2 
 
        
class Bullet(pygame.sprite.Sprite):
    def __init__(self):
        #Chamar o construtor da classe(Sprite)
        super().__init__()
 
        self.image = pygame.image.load('img/bullet.png')
 
        self.rect = self.image.get_rect()
 
    def update(self):
        #move a bullet
        self.rect.y -= 3


 
#inicia o Pygame
pygame.init()

 
#Criando a tela
screen_width = 800
screen_height = 600
screen = pygame.display.set_mode([screen_width, screen_height])

#Musica
music = pygame.mixer.music.load ("music/blassic.ogg")
pygame.mixer.music.play(-1)

#inicializa o módulo de fontes do Pygame
font_name = pygame.font.get_default_font()
game_font = pygame.font.SysFont(font_name, 72)

font = pygame.font.SysFont('Calibri', 25, True, False)

tempo_asteroid = 15
asteroids = []
delay = 30; 
t1 = pygame.time.get_ticks()

#Esplode a nave
'''explo_nave = {
    'img': pygame.image.load('img/ship_exploded.png').convert_alpha(),
    'move': [],
    'vel': {
        'x': 0,
        'y': 0
    },
    'rect': Rect(0, 0, 48, 48)
}'''



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

#função que detecta colição
def nave_colidiu():
    nave_rect = (player.rect)
    for asteroid in asteroids:
        if nave_rect.colliderect(rect(asteroid)):
            return True
    return False

animacao_colisao = 0
colidiu = False

################################################################################
#MENU
#carrega as imagens de botao iniciar e sair
p1 = pygame.image.load('img/iniciar.png') 
ex = pygame.image.load('img/sair.png')
# carrega background
bg = pygame.image.load('img/Fundo.jpg')
#carrega logo
logo = pygame.image.load('img/logo.png')

screen.blit( bg, (0,0)) #coloca a background na tela
screen.blit( logo, (150,20)) #coloca a logo na tela
screen.blit( p1, (240,300)) #coloca a iniciar na tela
screen.blit( ex, (240,350)) #coloca a sair na tela
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


#Lista de sprites
 
# Essa é a lista de a Player, asteroids e bullet
all_sprites_list = pygame.sprite.Group()
 
#Grupo de lista asteroids

asteroids_list = pygame.sprite.Group()
 
# Grupo de lista bullet
bullet_list = pygame.sprite.Group()
 
# Grupo de lista player
player = Player()
all_sprites_list.add(player)
all_sprites_list.add(asteroids)

asteroids_list.add(asteroids)
 
# Loop até o jogador clicar botao de fechar
done = False
 
#gerenciar rápido as atualizações de tela
clock = pygame.time.Clock()
 
score = 0

placar = font.render("Placar: " + str(score), 1, (0, 255, 255))


#Loop do Menu
while not done:
    #processo de evento 

    if not tempo_asteroid:
        tempo_asteroid = 15
        asteroids.append(listaAsteroide())
    else:
        tempo_asteroid -= 1

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True
 
        elif event.type == pygame.MOUSEBUTTONDOWN:
            #atira ao clicar com o mouse
            bullet = Bullet()
            #Posiçao da bala em relaçao a neve
            bullet.rect.x = player.rect.x + 22
            bullet.rect.y = player.rect.y 
            #adiciona a lista da bullet
            all_sprites_list.add(bullet)
            bullet_list.add(bullet)
 
    #Logica do jogo
     
    # chama a update() de todas as sprites
    all_sprites_list.update()


    #Calcula as mecanicas da Bullet
    '''for bullet in bullet_list:
 
        #Hit da bullet
        asteroids_hit_list = pygame.sprite.spritecollide(bullet, asteroids_list, True)
         
    #quando o asteroids leva o hit, remove a bullet e adicona ponto no score
        for asteroids in asteroids_hit_list:
            bullet_list.remove(bullet)
            all_sprites_list.remove(bullet)
            score += 1
            
            print(score)
 
        # Remove a bullet da tela
        if bullet.rect.y < -10:
            bullet_list.remove(bullet)
            all_sprites_list.remove(bullet)'''
 
    
    #blits e updates 
    screen.fill(BLACK)

    move_asteroids()
    
    for asteroid in asteroids:
       screen.blit(asteroid['img'], asteroid['move'])

    #verifica colisão
    '''if not colidiu:
        colidiu = nave_colidiu()
        player.rect.x += player.rect.x
        player.rect.y += player.rect.y
        placar = font.render("Placar: " + str(score), 1, (0, 255, 255))
        screen.blit(player)
    else:
        if not crash:
            crash = True
            player.rect.x += player.rect.x
            player.rect.y += player.rect.y

            screen.blit(player)
        elif animacao_colisao == 3:
            text = game_font.render('GAME OVER :C', 1, (255, 0, 0))
            ecra.blit(text, (250, 250))'''
    
    #Desenha todas as Sprites
    all_sprites_list.draw(screen)
    pygame.display.update()

    # FPS - calcula os milissegundos passados
    t2 = pygame.time.get_ticks() - t1;
    if t2 < delay:
        # espera o resto do tempo
        pygame.time.delay(delay - t2);
    
    #atualiza t1
    t1 = pygame.time.get_ticks()
    #update da tela
    pygame.display.update()
 
    #Limite de 20 frames por segundo
    clock.tick(60)
    remove_asteroids()
    
pygame.quit()
