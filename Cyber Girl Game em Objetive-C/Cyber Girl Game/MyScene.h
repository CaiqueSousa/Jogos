//
//  MyScene.h
//  Cyber Girl Game
//

//  Copyright (c) 2014 GABRIEL SOUZA DE OLIVEIRA. All rights reserved.
//

#import <SpriteKit/SpriteKit.h>
#import "PersonagemP.h"
#import "FMMParallaxNode.h"
#import "Score.h"

@interface MyScene : SKScene
{
    FMMParallaxNode *_parallaxNodeBackgrounds;
    FMMParallaxNode *_parallaxBackgroud2;
    FMMParallaxNode *_parallaxSpaceDust;
    FMMParallaxNode *_parallaxChao;
    
    SKSpriteNode *braco;
    
    SKSpriteNode *alienTiro;
}

@property PersonagemP *girl, *HP, *fundoBarraHP, *BarraHP, *rosto, *CoracaoHP1, *CoracaoHP2, *CoracaoHP3, *pontuacao;

-(void) gerarTiros;

@end
