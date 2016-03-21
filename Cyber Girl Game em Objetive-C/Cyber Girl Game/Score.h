//
//  Score.h
//  Cyber Girl Game
//
//  Created by ANDERSON CAIQUE DE SOUSA on 24/06/14.
//  Copyright (c) 2014 GABRIEL SOUZA DE OLIVEIRA. All rights reserved.
//

#import <SpriteKit/SpriteKit.h>


@interface Score : NSObject

+ (Score *) pontos;

@property NSInteger pontuacao;
@property NSInteger melhorPontucao;

- (void)salvarPontuacao;
- (void)pegarPontuacao;

- (void)gravarPontuacao:(int)pontos;

@end
