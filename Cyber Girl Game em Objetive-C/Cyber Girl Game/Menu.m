//
//  Menu.m
//  Cyber Girl Game
//
//  Created by ANDERSON CAIQUE DE SOUSA on 25/06/14.
//  Copyright (c) 2014 GABRIEL SOUZA DE OLIVEIRA. All rights reserved.
//

#import "Menu.h"
#import "MyScene.h"

@implementation Menu

-(id)initWithSize:(CGSize)size {
    if (self = [super initWithSize:size]) {
        NSString *imagem = [NSString stringWithFormat:@"MENU-PRONTO.png"];
        SKSpriteNode *fundo = [SKSpriteNode spriteNodeWithImageNamed:imagem];
        fundo.anchorPoint = CGPointZero;
        fundo.size = size;
        
        NSError *error;
        NSURL * backgroundMusicURL = [[NSBundle mainBundle] URLForResource:@"background" withExtension:@"mp3"];
        self.backgroundMusicPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:backgroundMusicURL error:&error];
        self.backgroundMusicPlayer.numberOfLoops = -1;
        [self.backgroundMusicPlayer prepareToPlay];
        [self.backgroundMusicPlayer play];
        
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
    }
    return self;
}

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    
    CGPoint touchLocation = [touch locationInNode:self];
    
    SKNode *node = [self nodeAtPoint:touchLocation];
    
    if ([node.name isEqualToString:@"jogar"]) {
        SKScene *sceneJogo = [[MyScene alloc] initWithSize:self.size];
        //SKTransition *transition = [SKTransition flipVerticalWithDuration:0.5];
        [self.view presentScene:sceneJogo];
    }else if ([node.name isEqualToString:@"sair"]){
        exit(0);
    }
}
@end
