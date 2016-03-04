//
//  MyScene.m
//  Cyber Girl Game
//
//  Created by GABRIEL SOUZA DE OLIVEIRA on 11/06/14.
//  Copyright (c) 2014 GABRIEL SOUZA DE OLIVEIRA. All rights reserved.
//

#import "MyScene.h"
#import "CasinhaFundo.h"
#import "FMMParallaxNode.h"
#import "GameOver.h"
#define kNumTiros  5
#define kNumTirosAliens  30
#define kNumAlien 15


@implementation MyScene

{


NSMutableArray *_GirlTiros, *_Alien, *_AlienG, *_TirosAliens;
int _nextGirlTiro, _nextAlien, _nextAlienG, _nextTiroAliens;
int pontos;
int tamanhoBarraDeVidaTotal;
int tamanhoBarraDeVidaAtual;
int qntdDeCoracoesTotal;
int qntdDeCoracoesAtual;

double _nextAlienSpawn, _nextAlienSpawnG;
    
SKLabelNode *pontuacao;
}


-(id)initWithSize:(CGSize)size {
    if (self = [super initWithSize:size]) {
        /* Setup your scene here */
        
        pontos = 0;
        _nextAlienSpawn = 0;
        tamanhoBarraDeVidaTotal = 10;
        tamanhoBarraDeVidaAtual = 10;
        qntdDeCoracoesTotal = 3;
        qntdDeCoracoesAtual = 3;
        
        
        for (SKSpriteNode *alien in _Alien) {
            alien.hidden = NO;
        }
        

        
        
        
        
        //INICIO adicionando backgroud
        
        SKSpriteNode *imagemDeFundo = [SKSpriteNode spriteNodeWithImageNamed:@"ceu .png"];
        imagemDeFundo.anchorPoint = CGPointMake(0, 0);
        imagemDeFundo.position = CGPointMake(-50, 20);
        [self addChild:imagemDeFundo];
        
        //fim
        
        
        
        
        //Chama metodo atirar
        
        [self gerarTiros];
        
        //INICIO Adicionando cenario fundo
        
#pragma mark - Game Backgrounds
        
        
        
        //1
        NSArray *parallaxNodeBackgroud2 = @[@"predios cinza escuro.png", @"predios cinza escuro.png"];
        CGSize planetSizes2 = CGSizeMake(200.0, 200.0);
        //2
        _parallaxBackgroud2 = [[FMMParallaxNode alloc] initWithBackgrounds:parallaxNodeBackgroud2
                                                                      size:planetSizes2
                                                      pointsPerSecondSpeed:10.0 espacamento:5 escala:1];

        //3
        _parallaxBackgroud2.position = CGPointMake(size.width/500.0, size.height/15.0);
        
        
        //4
        [self addChild:_parallaxBackgroud2];
        
        
        //1
        NSArray *parallaxNodeBackgroud = @[@"predios cinza.png", @"predios cinza.png"];
        CGSize planetSizes = CGSizeMake(200.0, 200.0);
        //2
        _parallaxNodeBackgrounds = [[FMMParallaxNode alloc] initWithBackgrounds:parallaxNodeBackgroud
                                                                           size:planetSizes
                                                           pointsPerSecondSpeed:20.0 espacamento:5 escala:1];

        //3
        _parallaxNodeBackgrounds.position = CGPointMake(size.width/500.0, size.height/9.0);
        
        
        //4
        [self addChild:_parallaxNodeBackgrounds];
        
        //1
        NSMutableArray *parallaxBackgroud2Names = [NSMutableArray arrayWithArray:@[@"predio 1.png", @"predio 2.png", @"predio 9.png", @"predio 3.png", @"predio 4.png", @"predio 5", @"predio 6", @"predio 7", @"predio 8", @"predio 10.png",@"predio 11",@"predio 12",@"predio 13"]];
        
        // Randomiza os predios em sequencia
        for(int i = 0; i < parallaxBackgroud2Names.count; i++)
        {
            // Escolhe uma posicao aleatoria
            int r = arc4random_uniform(parallaxBackgroud2Names.count);
            
            // Pega o predinho na posicao da sequencia
            NSString *predio = [parallaxBackgroud2Names objectAtIndex:i];
            
            // Tirar o predinho da lista
            [parallaxBackgroud2Names removeObjectAtIndex:i];
            // Colocar na posicao aleatoria que a gente escolheu
            [parallaxBackgroud2Names insertObject:predio atIndex:r];
        }
        
        //2
        _parallaxSpaceDust = [[FMMParallaxNode alloc] initWithBackgrounds:parallaxBackgroud2Names size:size pointsPerSecondSpeed:50.0 espacamento:5 escala:1];
        //3
        _parallaxSpaceDust.position = CGPointMake(0, 50);
        
        //4
        //[_parallaxSpaceDust randomizeNodesPositions];
        
        //5
        [self addChild:_parallaxSpaceDust];
        
#pragma mark - Setup Sprite for the ship
        
        // FIM do cenario fundo
        
        NSMutableArray *parallaxObjetos = [NSMutableArray arrayWithArray:@[@"box mail",@"Hidrante",@"box mail",@"Hidrante",@"box mail",@"Hidrante",@"box mail",@"Hidrante"]];
        
        // Randomiza os predios em sequencia
        for(int i = 0; i < parallaxObjetos .count; i++)
        {
            // Escolhe uma posicao aleatoria
            int r = arc4random_uniform(parallaxObjetos.count);
            
            // Pega o predinho na posicao da sequencia
            NSString *objetos = [parallaxObjetos  objectAtIndex:i];
            
            // Tirar o predinho da lista
            [parallaxObjetos  removeObjectAtIndex:i];
            // Colocar na posicao aleatoria que a gente escolheu
            [parallaxObjetos  insertObject:objetos atIndex:r];
        }
        
        

        
        CasinhaFundo*fundo=[[CasinhaFundo alloc] init];
        [self addChild:fundo];
        
        //ADICONADO O CHAO
        //for (int i = 0; i < 12; i++) {
            //SKSpriteNode *tileChao = [SKSpriteNode spriteNodeWithImageNamed:@"Tile chao(Cyber Girl Force).png"];
            //tileChao.anchorPoint = CGPointMake(0, 0);
            //tileChao.position = CGPointMake(i*tileChao.frame.size.width, 0);
          //[self addChild:tileChao];
            //FIM
            /*NSMutableArray *tileChaoArray = [NSMutableArray arrayWithArray:@[@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png"]];
            _parallaxChao = [[FMMParallaxNode alloc] initWithBackgrounds:tileChaoArray size:size pointsPerSecondSpeed:50.0 definirEspaco:1];
        
       //_parallaxChao.position = CGPointMake(i*tileChao.frame.size.width, 0);
            [self addChild:_parallaxChao];*/
            
       // }
        
      //  for (int i = 0; i < 12; i++) {
           // SKSpriteNode *tileChao = [SKSpriteNode spriteNodeWithImageNamed:@"Tile chao(Cyber Girl Force).png"];
            //tileChao.anchorPoint = CGPointMake(0, 0);
            //tileChao.position = CGPointMake(i*tileChao.frame.size.width, 0);
            //[self addChild:tileChao];
            //FIM
       
       // }
        
        
        
#pragma mark - TBD - Setup the asteroids add
        
        //adicionando inimigo (alien)
        
        _Alien = [[NSMutableArray alloc] initWithCapacity:kNumAlien];
        for (int i = 0; i < kNumAlien; ++i) {
            SKSpriteNode *alien = [SKSpriteNode spriteNodeWithImageNamed:@"alien1.png"];
            alien.hidden = YES;
            [alien setXScale:0.5];
            [alien setYScale:0.5];
            
            
            
            SKTextureAtlas *atlas = [SKTextureAtlas atlasNamed:@"Alien"];
            SKTexture *A1 = [atlas textureNamed:@"alien1.png"];
            SKTexture *A2 = [atlas textureNamed:@"alien2.png"];
            SKTexture *A3 = [atlas textureNamed:@"alien3.png"];
            SKTexture *A4 = [atlas textureNamed:@"alien4.png"];
            SKTexture *A5 = [atlas textureNamed:@"alien5.png"];
            
            NSArray *andando = @[A1,A2, A3, A4, A5];
            SKAction *andar = [SKAction animateWithTextures:andando timePerFrame:0.1];
            
            [alien runAction: [SKAction repeatActionForever:andar]];
                        
            
            
            
            
            
            
            
            [_Alien addObject:alien];
            [self addChild:alien];
        }
        
        
        
        
        //adicionando inimigo (alien)
        
        _AlienG = [[NSMutableArray alloc] initWithCapacity:kNumAlien];
        for (int i = 0; i < kNumAlien; ++i) {
            SKSpriteNode *alien = [SKSpriteNode spriteNodeWithImageNamed:@"alien1.png"];
            alien.hidden = YES;
            [alien setXScale:1.2];
            [alien setYScale:1.2];
            
            
            
            SKTextureAtlas *atlas = [SKTextureAtlas atlasNamed:@"Alien"];
            SKTexture *A1 = [atlas textureNamed:@"alien1.png"];
            SKTexture *A2 = [atlas textureNamed:@"alien2.png"];
            SKTexture *A3 = [atlas textureNamed:@"alien3.png"];
            SKTexture *A4 = [atlas textureNamed:@"alien4.png"];
            SKTexture *A5 = [atlas textureNamed:@"alien5.png"];
            
            NSArray *andando = @[A1,A2, A3, A4, A5];
            SKAction *andar = [SKAction animateWithTextures:andando timePerFrame:0.1];
            
            [alien runAction: [SKAction repeatActionForever:andar]];
            
            
            
            
            
            
            
            
            [_AlienG addObject:alien];
            [self addChild:alien];
        }
        
        
        
        
        
        
        
        
        
        NSArray *tileChao = @[@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png",@"Tile chao(Cyber Girl Force).png"];
        _parallaxChao = [[FMMParallaxNode alloc]initWithBackgrounds:tileChao size:CGSizeZero pointsPerSecondSpeed:70.0 espacamento:0 escala:1];
        
        [self addChild:_parallaxChao];
        
        
        
        //Personagem
        
        self.girl=[PersonagemP spriteNodeWithImageNamed:@"andando1.png"];
        self.girl.anchorPoint = CGPointMake(0, 0);
        self.girl.position = CGPointMake(50, 50);
        
        SKTextureAtlas *atlas = [SKTextureAtlas atlasNamed:@"andando"];
        SKTexture *A1 = [atlas textureNamed:@"andando1.png"];
        SKTexture *A2 = [atlas textureNamed:@"andando2.png"];
        SKTexture *A3 = [atlas textureNamed:@"andando3.png"];
        SKTexture *A4 = [atlas textureNamed:@"andando4.png"];
        SKTexture *A5 = [atlas textureNamed:@"andando5.png"];
        
        NSArray *andando = @[A1,A2, A3, A4, A5];
        SKAction *andar = [SKAction animateWithTextures:andando timePerFrame:0.1];
        
        [self.girl runAction: [SKAction repeatActionForever:andar]];
        
        //
        braco = [SKSpriteNode spriteNodeWithImageNamed:@"braco1.png"];
        braco.position = CGPointMake(30, 18);
        braco.zPosition = -1;
        braco.name = @"braco";
        braco.anchorPoint = CGPointMake(0, 0);
        
        self.girl.zPosition = 10;
        
        [self.girl addChild:braco];
        [self addChild:self.girl];
        //FIM
        
        
        
        
        //FUNDO HP
        
        self.HP=[PersonagemP spriteNodeWithImageNamed:@"fundo.png"];
        self.HP.anchorPoint = CGPointMake(0, 0);
        self.HP.position = CGPointMake(40, 6);
        
        [self.HP setScale:0.3];
        
        [self addChild:self.HP];
        
        //fundo BARRA HP
        
        self.fundoBarraHP=[PersonagemP spriteNodeWithImageNamed:@"fundoBarraHP.png"];
        self.fundoBarraHP.anchorPoint = CGPointMake(0, 0);
        self.fundoBarraHP.position = CGPointMake(78, 25);
        
        [self.fundoBarraHP setScale:0.3];
        
        [self addChild:self.fundoBarraHP];
        
        //BARRA HP
        
        self.BarraHP=[PersonagemP spriteNodeWithImageNamed:@"BarraHP.png"];
        self.BarraHP.anchorPoint = CGPointMake(0, 0);
        self.BarraHP.position = CGPointMake(78.8, 25.8);
        
        [self.BarraHP setScale:0.3];
        
        [self addChild:self.BarraHP];
        
        
        //ROSTO GIRL
        
        self.rosto=[PersonagemP spriteNodeWithImageNamed:@"rostoNormal.png"];
        self.rosto.anchorPoint = CGPointMake(0, 0);
        self.rosto.position = CGPointMake(40, 6);
        
        [self.rosto setScale:0.3];
        
        [self addChild:self.rosto];
        
        
        //CORACAO
        
        self.CoracaoHP1=[PersonagemP spriteNodeWithImageNamed:@"CoracaoHP1.png"];
        self.CoracaoHP1.anchorPoint = CGPointMake(0, 0);
        self.CoracaoHP1.position = CGPointMake(82.8, 13.9);
        
        [self.CoracaoHP1 setScale:0.3];
        
        [self addChild:self.CoracaoHP1];
        //CORACAO
        
        self.CoracaoHP2=[PersonagemP spriteNodeWithImageNamed:@"CoracaoHP2.png"];
        self.CoracaoHP2.anchorPoint = CGPointMake(0, 0);
        self.CoracaoHP2.position = CGPointMake(92.8, 13.9);
        
        [self.CoracaoHP2 setScale:0.3];
        
        [self addChild:self.CoracaoHP2];
        //CORACAO
        
        self.CoracaoHP3=[PersonagemP spriteNodeWithImageNamed:@"CoracaoHP3.png"];
        self.CoracaoHP3.anchorPoint = CGPointMake(0, 0);
        self.CoracaoHP3.position = CGPointMake(102.8, 13.9);
        
        [self.CoracaoHP3 setScale:0.3];
        
        [self addChild:self.CoracaoHP3];
        
        
        
        
        
        
        //FUNDO HP
        
        self.HP=[PersonagemP spriteNodeWithImageNamed:@"fundo2.png"];
        
        self.HP.position = CGPointMake(305, 25);
        
        
        
        [self addChild:self.HP];

        
        
        //PONTUAÇ˜AO
        
        pontuacao = [[SKLabelNode alloc]initWithFontNamed:@"CourierNewPS-BoldMT"];
        [pontuacao setPosition:CGPointMake(306, 22)];
        [pontuacao setColor:[UIColor whiteColor]];
        [pontuacao setFontSize:12];
        
        NSString *textoPontos = [NSString stringWithFormat:@"Pontos: %i",pontos];
        [pontuacao setText:textoPontos];
        
        
        
        [self addChild:pontuacao];
        
        
        
        
        
        
        
        //Chama metodo atirar
        [self gerarTiros];
        
        for (SKSpriteNode *tiro in _GirlTiros) {
            tiro.hidden = YES;
        }
        
    }
    return self;
    
}


- (float)randomValueBetween:(float)low andValue:(float)high {
    return (((float) arc4random() / 0xFFFFFFFFu) * (high - low)) + low;
}



-(void)update:(CFTimeInterval)currentTime {
    /* Called before each frame is rendered */
    
    [_parallaxNodeBackgrounds update:currentTime];
    [_parallaxBackgroud2 update:currentTime];
    [_parallaxSpaceDust update:currentTime];
    [_parallaxChao update:currentTime];
  
    
    
    //ALIEN PEQUENO
    
    double curTime = CACurrentMediaTime();
    if (curTime > _nextAlienSpawn) {
        float randSecs = [self randomValueBetween:0.20 andValue:1.0];
        _nextAlienSpawn = randSecs + curTime;
        
        float randY = [self randomValueBetween:50 andValue:self.frame.size.height];
        float randDuration = [self randomValueBetween:2.0 andValue:10.0];
        
        SKSpriteNode *alien = [_Alien objectAtIndex:_nextAlien];
        _nextAlien++;
        
        if (_nextAlien >= _Alien.count) {
            _nextAlien = 0;
        }
        
        [alien removeAllActions];
        
        
        SKTextureAtlas *atlas = [SKTextureAtlas atlasNamed:@"Alien"];
        SKTexture *A1 = [atlas textureNamed:@"alien1.png"];
        SKTexture *A2 = [atlas textureNamed:@"alien2.png"];
        SKTexture *A3 = [atlas textureNamed:@"alien3.png"];
        SKTexture *A4 = [atlas textureNamed:@"alien4.png"];
        SKTexture *A5 = [atlas textureNamed:@"alien5.png"];
        
        NSArray *andando = @[A1,A2, A3, A4, A5];
        SKAction *andar = [SKAction animateWithTextures:andando timePerFrame:0.1];
        
        [alien runAction: [SKAction repeatActionForever:andar]];

        alien.colorBlendFactor = 0.5f;
        
        
        alien.position = CGPointMake(self.frame.size.width+alien.size.width/2, randY);
        alien.hidden = NO;
        
        CGPoint location = CGPointMake(-self.frame.size.width-alien.size.width, randY);
        
        SKAction *moveAction = [SKAction moveTo:location duration:randDuration];
        SKAction *doneAction = [SKAction runBlock:(dispatch_block_t)^() {
            alien.hidden = YES;
        }];
        
        SKAction *moveAlienActionWithDone = [SKAction sequence:@[moveAction, doneAction]]
        ;
        [alien runAction:moveAlienActionWithDone withKey:@"alienMoving"];
    }
    
    
    //ALIEN GRANDE
    
    double curTimeG = CACurrentMediaTime();
    if (curTimeG > _nextAlienSpawnG) {
        float randSecs = [self randomValueBetween:0.20 andValue:1.0];
        _nextAlienSpawnG = randSecs + curTime;
        
        float randY = [self randomValueBetween:50 andValue:self.frame.size.height];
        float randDuration = [self randomValueBetween:2.0 andValue:10.0];
        
        SKSpriteNode *alien = [_AlienG objectAtIndex:_nextAlienG];
        _nextAlienG++;
        
        if (_nextAlienG >= _Alien.count) {
            _nextAlienG = 0;
        }
        
        [alien removeAllActions];
        
        
        SKTextureAtlas *atlas = [SKTextureAtlas atlasNamed:@"Alien"];
        SKTexture *A1 = [atlas textureNamed:@"alien1.png"];
        SKTexture *A2 = [atlas textureNamed:@"alien2.png"];
        SKTexture *A3 = [atlas textureNamed:@"alien3.png"];
        SKTexture *A4 = [atlas textureNamed:@"alien4.png"];
        SKTexture *A5 = [atlas textureNamed:@"alien5.png"];
        
        NSArray *andando = @[A1,A2, A3, A4, A5];
        SKAction *andar = [SKAction animateWithTextures:andando timePerFrame:0.1];
        
        [alien runAction: [SKAction repeatActionForever:andar]];
        
        
        
        
        alien.position = CGPointMake(self.frame.size.width+alien.size.width/2, randY);
        alien.hidden = NO;
        
        CGPoint location = CGPointMake(-self.frame.size.width-alien.size.width, randY);
        
        SKAction *moveAction = [SKAction moveTo:location duration:randDuration];
        SKAction *doneAction = [SKAction runBlock:(dispatch_block_t)^() {
            alien.hidden = YES;
        }];
        
        SKAction *moveAlienActionWithDone = [SKAction sequence:@[moveAction, doneAction]]
        ;
        [alien runAction:moveAlienActionWithDone withKey:@"alienMoving"];
    }
    
    for (SKSpriteNode *alien in _AlienG) {
        if (arc4random()%100 == 1 && alien.hidden == FALSE && alien.position.x >= 50) {
            
            alienTiro = [_TirosAliens objectAtIndex:_nextTiroAliens];
            _nextTiroAliens++;
            if (_nextTiroAliens >= _TirosAliens.count) {
                _nextTiroAliens = 0;
            }
            
            
            
            alienTiro.position = alien.position;
            alienTiro.hidden = NO;
            [alienTiro removeAllActions];
            
            alienTiro.zPosition = 8;
            
            float dx = (self.girl.position.x + [self randomValueBetween:-60 andValue:+60]) - alien.position.x;
            float dy = (self.girl.position.y + [self randomValueBetween:-60 andValue:+60]) - alien.position.y;
            float angulo = atan2f(dy, dx);
            
            float x1 = cosf(angulo) * self.frame.size.width*2;
            float y1 = sinf(angulo) * self.frame.size.width*2;
            
            CGPoint location = CGPointMake(alienTiro.position.x + x1, alienTiro.position.y + y1);
            
            SKAction *laserMoveAction = [SKAction moveTo:location duration:6.5];
            
            SKAction *tiroDoneAction = [SKAction runBlock:(dispatch_block_t)^() {
                alienTiro.hidden = YES;
            }];
            
            
            SKAction *moveTiroActionWithDone = [SKAction sequence:@[laserMoveAction, tiroDoneAction]];
            
            
            [alienTiro runAction:moveTiroActionWithDone withKey:@"TiroFired"];
            
            // Roda a bala, em relacao ao ponto que a gente calculou ali em cima
            alienTiro.zRotation = angulo;
            
        }
        
    }
    
    
    
    
    //check for laser collision with asteroid
    for (SKSpriteNode *alien in _AlienG) {
        if (alien.hidden) {
            continue;
        }
        for (SKSpriteNode *girlTiro in _GirlTiros) {
            if (girlTiro.hidden) {
                continue;
            }
            
            if ([girlTiro intersectsNode:alien]) {
                girlTiro.hidden = YES;
                alien.hidden = YES;
                
                NSLog(@"you just destroyed an alien");
                
                [self runAction:[SKAction playSoundFileNamed:@"explosao do inimigo 1.WAV" waitForCompletion:NO]];
                
                //cores aleatorias
                CGFloat hue = ( arc4random() % 256 / 256.0 );  //  0.0 to 1.0
                CGFloat saturation = ( arc4random() % 128 / 256.0 ) + 0.5;  //  0.5 to 1.0, away from white
                CGFloat brightness = ( arc4random() % 128 / 256.0 ) + 0.5;  //  0.5 to 1.0, away from black
                UIColor *color = [UIColor colorWithHue:hue saturation:saturation brightness:brightness alpha:1];
                
                //label de dano!
                SKLabelNode *dano = [SKLabelNode labelNodeWithFontNamed:@"CourierNewPS-BoldMT"];
                [dano setPosition:alien.position];
                [dano setFontSize:15];
                [dano setFontColor:color];
                [dano setText:@"10"];
                [self addChild:dano];
                
                //animação do dano
                //subindo
                SKAction *subindo = [SKAction moveByX:0 y:10 duration:1];
                //sumindo
                SKAction *sumindo = [SKAction fadeOutWithDuration:1];
                [dano runAction:subindo];
                [dano runAction:sumindo];
                
                [self aumentaPontos];
                continue;
            }
        }
        
        
        if ([_girl intersectsNode:alien]) {
            alien.hidden = YES;
            [self tomarDano];
            NSLog(@"alien acertou com o corpo");
        }
        
        for (SKSpriteNode *tiroAlien in _TirosAliens) {
            if (tiroAlien.hidden) {
                continue;
            }
            
            if ([tiroAlien intersectsNode:self.girl]) {
                [self tomarDano];
                tiroAlien.hidden = YES;
                
                //sprite girl levando o tiro
                
                NSLog(@"levou tiro");
                
                //diminui uma vida
                continue;
            }
        }
    }
    
    for (SKNode *balaJogador in _GirlTiros) {
        if (balaJogador.hidden == TRUE) {
            continue;
        }
        for (SKNode *balaInimigo in _TirosAliens) {
            if (balaInimigo.hidden == TRUE) {
                continue;
            }if ([balaJogador intersectsNode:balaInimigo]) {
                balaJogador.hidden = TRUE;
                balaInimigo.hidden = TRUE;
            }
        }
    }


}

- (void) tomarDano {
    
    SKAction *blink = [SKAction sequence:@[[SKAction fadeOutWithDuration:0.1],
                                           [SKAction fadeInWithDuration:0.1]]];
    SKAction *blinkForTime = [SKAction repeatAction:blink count:4];
    [_girl runAction:blinkForTime];
    
    tamanhoBarraDeVidaAtual--;
    
    if (tamanhoBarraDeVidaAtual <= 0) {
        tamanhoBarraDeVidaAtual = tamanhoBarraDeVidaTotal;
        qntdDeCoracoesAtual--;
        if (self.CoracaoHP3.hidden == FALSE) {
            self.CoracaoHP3.hidden = TRUE;
        }else if (self.CoracaoHP2.hidden == FALSE) {
            self.CoracaoHP2.hidden = TRUE;
        }else if (self.CoracaoHP1.hidden == FALSE) {
            self.CoracaoHP1.hidden = TRUE;
            [self matarPersonagem];
            return;
        }
    }
    self.BarraHP.xScale = (float)tamanhoBarraDeVidaAtual/tamanhoBarraDeVidaTotal*0.3;
    
    SKAction *animarRosto = [SKAction setTexture:[SKTexture textureWithImageNamed:@"rostoLevandoDano.png"]];
    SKAction *esperarTempo = [SKAction waitForDuration:0.5];
    SKAction *rostoNormal = [SKAction setTexture:[SKTexture textureWithImageNamed:@"rostoNormal.png"]];
    
    if (qntdDeCoracoesAtual == 1) {
        rostoNormal = [SKAction setTexture:[SKTexture textureWithImageNamed:@"rostoQuaseMorrendo"]];
    }
    
    [self.rosto removeAllActions];
    
    [self.rosto runAction:[SKAction sequence:@[animarRosto, esperarTempo, rostoNormal]]];
}

- (void) matarPersonagem {
    //[Score pontos].pontuacao = pontos;
    [[Score pontos] gravarPontuacao:pontos];
    
    SKScene *sceneJogo = [[GameOver alloc] initWithSize:self.size];
    [self.view presentScene:sceneJogo];
}

-(void) aumentaPontos{
    pontos += 10;
    NSString *textoPontos = [NSString stringWithFormat:@"pontos: %i",pontos];
    [pontuacao setText:textoPontos];
    
    NSLog(@"pontos: %i", pontos);
}




//INICIO //Metodo de atirar


-(void)gerarTiros{
    
    _GirlTiros = [[NSMutableArray alloc] initWithCapacity:kNumTiros];
    for (int i = 0; i < kNumTiros; ++i) {
        SKSpriteNode *GirlTiro = [SKSpriteNode spriteNodeWithImageNamed:@"tiroDaPistola1.png"];
        GirlTiro.hidden = YES;
        [_GirlTiros addObject:GirlTiro];
        [self addChild:GirlTiro];
    }
    
    
    
    _TirosAliens = [[NSMutableArray alloc] initWithCapacity:kNumTirosAliens];
    for (int i = 0; i < kNumTirosAliens; ++i) {
        SKSpriteNode *TirosAliens = [SKSpriteNode spriteNodeWithImageNamed:@"tiroDaPistolaAlien1.png"];
        TirosAliens.hidden = YES;
        [_TirosAliens addObject:TirosAliens];
        [self addChild:TirosAliens];
        
    }
    
    
    
}
//FIM //Metodo de atirar

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    //Quando toca na tela
    
    SKSpriteNode *GirlTiro = [_GirlTiros objectAtIndex:_nextGirlTiro];
    _nextGirlTiro++;
    if (_nextGirlTiro >= _GirlTiros.count) {
        _nextGirlTiro = 0;
    }
    
    //CGPoint tocouNaTela = [[touches anyObject] locationInNode:self];
    
    // Pega onde ele tocou, em relacao a girl
    CGPoint tocou = [[touches anyObject] locationInNode:self.girl];
    
    // Joga o ponto, em relacao ao braco
    tocou.x -= braco.position.x;
    tocou.y -= braco.position.y;
    
    // Roda o braco, em relacao ao ponto que a gente calculou ali em cima
    braco.zRotation = atan2f(tocou.y, tocou.x);
    
    GirlTiro.position = [braco convertPoint:CGPointMake(25, 5) toNode:self];
    GirlTiro.hidden = NO;
    [GirlTiro removeAllActions];
    
    GirlTiro.zPosition = 8;
    
    float x1 = cosf(braco.zRotation) * self.frame.size.width;
    float y1 = sinf(braco.zRotation) * self.frame.size.width ;
    
    CGPoint location = CGPointMake(GirlTiro.position.x + x1, GirlTiro.position.y + y1);
    
    SKAction *laserMoveAction = [SKAction moveTo:location duration:0.5];
    
    SKAction *tiroDoneAction = [SKAction runBlock:(dispatch_block_t)^() {
        GirlTiro.hidden = YES;
    }];
    
    
    SKAction *moveTiroActionWithDone = [SKAction sequence:@[laserMoveAction, tiroDoneAction]];
    
    
    [GirlTiro runAction:moveTiroActionWithDone withKey:@"TiroFired"];
    
    [self runAction:[SKAction playSoundFileNamed:@"Tiro1.wav" waitForCompletion:NO]];
    
    // Roda a bala, em relacao ao ponto que a gente calculou ali em cima
    GirlTiro.zRotation = atan2(tocou.y , tocou.x);
}






@end



