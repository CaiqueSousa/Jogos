//
//  Score.m
//  Cyber Girl Game
//
//  Created by ANDERSON CAIQUE DE SOUSA on 24/06/14.
//  Copyright (c) 2014 GABRIEL SOUZA DE OLIVEIRA. All rights reserved.
//

#import "Score.h"
#import "MyScene.h"

@implementation Score

+ (Score *) pontos
{
    static Score *pontos = nil;
    if (!pontos)
    {
        pontos = [[super allocWithZone:nil] init];
    }
    return pontos;
}

+ (id)allocWithZone: (struct _NSZone *)zone
{
    return [self pontos];
}

- (id)init
{
    self = [super init];
    if (self)
    {
    }
    return self;
}

- (void)salvarPontuacao
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [defaults setInteger:[[Score pontos] pontuacao] forKey:@"score"];
    [defaults synchronize];
}

- (void)pegarPontuacao
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [[Score pontos] setMelhorPontucao:[defaults integerForKey:@"score"]];
}

- (void)gravarPontuacao:(int)pontos
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    
    self.pontuacao = pontos;
    NSInteger highscore = [defaults integerForKey:@"score"];
    
    if(highscore < pontos){
        [defaults setInteger:pontos forKey:@"score"];
        self.melhorPontucao = pontos;
    }
}

@end
