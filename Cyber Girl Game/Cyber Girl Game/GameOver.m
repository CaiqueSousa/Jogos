//
//  GameOver.m
//  Cyber Girl Game
//
//  Created by ANDERSON CAIQUE DE SOUSA on 27/06/14.
//  Copyright (c) 2014 GABRIEL SOUZA DE OLIVEIRA. All rights reserved.
//

#import "GameOver.h"
#import "Menu.h"
#import "MyScene.h"
#import "Score.h"

@implementation GameOver

-(id)initWithSize:(CGSize)size {
    if (self = [super initWithSize:size]) {
        NSString *imagem = [NSString stringWithFormat:@"score.png"];
        SKSpriteNode *fundo = [SKSpriteNode spriteNodeWithImageNamed:imagem];
        fundo.anchorPoint = CGPointZero;
        fundo.size = size;
        
        /* NSError *error;
         NSURL * backgroundMusicURL = [[NSBundle mainBundle] URLForResource:@"background" withExtension:@"mp3"];
         self.backgroundMusicPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:backgroundMusicURL error:&error];
         self.backgroundMusicPlayer.numberOfLoops = -1;
         [self.backgroundMusicPlayer prepareToPlay];
         [self.backgroundMusicPlayer play];*/
        
        SKSpriteNode * btnJogar = [[SKSpriteNode alloc] init];
        //btnJogar.color = [SKColor colorWithRed:0.5 green:0.5 blue:0.5 alpha:1.0];
        btnJogar.size = CGSizeMake(200, 30);
        btnJogar.position = CGPointMake(490, 75);
        btnJogar.name = [NSString stringWithFormat:@"jogar"];
        
        SKSpriteNode * btnSair = [[SKSpriteNode alloc] init];
        //btnJogar.color = [SKColor colorWithRed:0.5 green:0.5 blue:0.5 alpha:1.0];
        btnSair.size = CGSizeMake(200, 30);
        btnSair.position = CGPointMake(490, 30);
        btnSair.name = [NSString stringWithFormat:@"sair"];
        
        [self addChild:fundo];
        [self addChild:btnJogar];
        [self addChild:btnSair];
        
        self.pontuacao = [[SKLabelNode alloc]initWithFontNamed:@"CourierNewPS-BoldMT"];
        [self.pontuacao setColor:[UIColor whiteColor]];
        [self.pontuacao setFontSize:12];
        
        NSString *textoPontos = [NSString stringWithFormat:@"Score: %li",(long)[[Score pontos] pontuacao]];
        [self.pontuacao setText:textoPontos];
        self.pontuacao.position = CGPointMake(225, 160);
        
        self.melhor = [[SKLabelNode alloc]initWithFontNamed:@"CourierNewPS-BoldMT"];
        [self.melhor setColor:[UIColor whiteColor]];
        [self.melhor setFontSize:12];
        
        [self.melhor setText:[NSString stringWithFormat:@" High Score: %li", [Score pontos].melhorPontucao]];
        self.melhor.position = CGPointMake(225, 120);
        
        
        
        [self addChild:self.pontuacao];
        [self addChild:self.melhor];
    }
    return self;
}

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    
    CGPoint touchLocation = [touch locationInNode:self];
    
    SKNode *node = [self nodeAtPoint:touchLocation];
    
    if ([node.name isEqualToString:@"jogar"]) {
        SKScene *sceneScore = [[MyScene alloc] initWithSize:self.size];
        //SKTransition *transition = [SKTransition flipVerticalWithDuration:0.5];
        [self.view presentScene:sceneScore];
    }else if ([node.name isEqualToString:@"sair"]){
        SKScene *sceneScore = [[Menu alloc] initWithSize:self.size];
        //SKTransition *transition = [SKTransition flipVerticalWithDuration:0.5];
        [self.view presentScene:sceneScore];
    }
}

@end
