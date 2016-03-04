//
//  Logo.m
//  Cyber Girl Game
//
//  Created by ANDERSON CAIQUE DE SOUSA on 27/06/14.
//  Copyright (c) 2014 GABRIEL SOUZA DE OLIVEIRA. All rights reserved.
//

#import "Logo.h"
#import "Menu.h"

@implementation Logo

-(id)initWithSize:(CGSize)size {
    if (self = [super initWithSize:size]) {
        NSString *imagem = [NSString stringWithFormat:@"logo da equipe.png"];
        SKSpriteNode *fundo = [SKSpriteNode spriteNodeWithImageNamed:imagem];
        fundo.anchorPoint = CGPointZero;
        fundo.alpha = 0.0;
        fundo.size = size;
        
        //aparecendo
        SKAction *aparecendo = [SKAction fadeInWithDuration:2];
        
        //sumindo
        SKAction *sumindo = [SKAction fadeOutWithDuration:2];
        
        SKAction *sequencia = [SKAction sequence:@[aparecendo, sumindo]];
        [fundo runAction:sequencia];
        
        self.currentTime1 = CACurrentMediaTime();
        
        [self addChild:fundo];
        
    }
    return self;
}

- (void)ChamarOMenu{
    SKScene *sceneJogo = [[Menu alloc] initWithSize:self.size];
    [self.view presentScene:sceneJogo];
}

-(void)update:(NSTimeInterval)currentTime{
    if(CACurrentMediaTime() - self.currentTime1 >= 4){
        NSLog(@"Passou");
        [self ChamarOMenu];
    }
}

@end
