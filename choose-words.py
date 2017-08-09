'''
Jogo de palavras aleatorias e marcação de pontos.
'''
import time
import sys
import random
from threading import Timer


#declaração de variaveis
menuAtivo = True
jogoAtivo = True
ponto = 0

#vetores
palavras = ['some','each','time','but','there','word','after','work','get','back','fuzil','desapercebido','acelerado','cavaleiro','comprimento','flagrante','vultuoso','retificar','preeminente','completamente','emergir','distinto','cachorro','cadeira','bolsa','mesa','luva','independencia','amor','caminhos','chuva','coragem','perigo','cumplicidade','entercener', 'esperança', 'felicidade', 'gentileza', 'infinito', 'liberdade', 'melancolia','palimpsesto', 'paz','perfeitamente','reciprocidade','recomeçar','respeito','risos','saudade','sentir','singularidades','sublime','vida']

#inicio Arquivo de pontuação
arq = open ("pontuação.txt", "r")
pontuacao = arq.readlines()


#Menu
opcao = int (input("\n\n\n\n=======================================================================\n"+
                   "                          Choose Words Speed \n"
                   "=======================================================================\n" +
                   "\t\t\t  Tecla 1   Iniciar o jogo.\n"+
                   "\t\t\t  Tecla 2   CRÉDITOS.\n"+ 
                   "\n=======================================================================\n"+
                   "=======================================================================\n\n\n\n\n\n\n\n\n"))

while(menuAtivo == True):
    if(opcao == 1):
        jogador = input("Digite Seu nome: ")
        print("Voce tem 45 segundos para responder o maximo de respostas\n")
        menuAtivo = False
        jogoAtivo = True
        break
    elif(opcao == 2):
        print("Dev: Anderson Caique de Sousa")
    elif(opcao == 3):
        menuAtivo = False
        jogoAtivo = False
        break
    else:
        print("\nErro\n")

    opcao = int (input())

#FIM Menu

#Tempo
timeout = 45
t = Timer(timeout, print, ['O tempo acabou\n'])
t.start()
ch2 = "Digite antes de %dsg: \n" % timeout
start_time = time.time()

random.shuffle(palavras)
tempo = time.time() - start_time
aux = random.choice(palavras)
print("Palavra: ", aux)

print("||==========||Adivinhe a palavra||==========|| \n")    

   
#Loop do jogo 
while jogoAtivo == True:
    i = 0
  
    print("Digite a palavra: ")
    ch = input(ch2)
       
    if aux == ch:
        ponto = ponto+1
        print("ACERTOU!! Pontos:%d" % ponto,"\n")
        aux = random.choice(palavras)
        print("A Palavra mudou agora é:", aux,"\n")
        
        
        if ponto == 10:
            print("====|| Bonûs!!! ||====")
            ponto = ponto+2
            
        if ponto == 20:
            print("====|| Bonûs!!! ||====")
            ponto = ponto+3

        if ponto == 30:
            print("====|| Bonûs!!! ||====")
            ponto = ponto+4
            
        if ponto == 40:
            print("====|| Bonûs!!! ||====")
            ponto = ponto+5
            
        if ponto == 50:
            print("====|| Bonûs!!! ||====")
            ponto = ponto+6    
                
            

    elif True:
        print("ERROU!! a palavra era:", aux ,", Pontos:", ponto)
        time.sleep(1.5)
        t.cancel()
        print("Voce levou para completar %s segundos" % (time.time() - start_time))
        break
    
#Fim Loop do jogo
print ("\nFim de Jogo")

#Final Arquivo de pontuação
pontuacao = (ponto)
arq = open ("pontuação.txt", "w")
arq.writelines(str(jogador))
arq.writelines(str(pontuacao))
arq.writelines(str(tempo))
arq.close()
