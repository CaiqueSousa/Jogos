#Alunos: Anderson Caique de Sousa, Lucas Santos de Almeida, Renato Kajiwara
import pygame,sys
import random
from pygame.locals import *
from sys import exit
from random import randrange
 
# Define some colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)
BLUE = (0, 0, 255)

#Classes
 
 
class Block(pygame.sprite.Sprite):
    def __init__(self, color):
        #Chamar o construtor da classe(Sprite)
        super().__init__()
 
        self.image = pygame.image.load('img/asteroids.png')
        
 
        self.rect = self.image.get_rect()
 
 
 
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


 

 
#Inicia o pygame
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

asteroids = []

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
block_list = pygame.sprite.Group()
 
#Grupo de lista bullet
bullet_list = pygame.sprite.Group()
 
#Cria os asteroids
 
for i in range(50):
    #asteroid
    block = Block(BLUE)
 
    #Posiçao randomica do asteroid
    block.rect.x = random.randrange(screen_width)
    block.rect.y = random.randrange(350)
 
    #adiciona os a lista de asteroids
    block_list.add(block)
    all_sprites_list.add(block)
 
# Grupo de lista player
player = Player()
all_sprites_list.add(player)
 
#Loop até o jogador clicar botao de fechar
done = False
 
#gerenciar rápido as atualizações de tela
clock = pygame.time.Clock()
 
score = 0
player.rect.y = 340
player.rect.x = 600
placar = font.render("Placar: " + str(score), 1, (0, 255, 255))

#Loop do Menu
while not done:
    #processo de evento
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
    for bullet in bullet_list:
        #Hit da bullet
        block_hit_list = pygame.sprite.spritecollide(bullet, block_list, True)
         
        #quando o asteroids leva o hit, remove a bullet e adicona ponto no score
        for block in block_hit_list:
            bullet_list.remove(bullet)
            all_sprites_list.remove(bullet)
            score += 1
            
            print(score)
 
        # Remove a bullet da tela
        if bullet.rect.y < -10:
            bullet_list.remove(bullet)
            all_sprites_list.remove(bullet)
            
        screen.blit(placar, (0, 0))


    #Desenha todas as Sprites
    all_sprites_list.draw(screen)
    pygame.display.update() 
       
    #blits e updates 
    screen.fill(BLACK)
 

 
    #Limite de 20 frames por segundo
    clock.tick(60)
 
pygame.quit()
