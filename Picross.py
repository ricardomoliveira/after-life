# Grupo 028
# TagusPark

# Ricardo Oliveira 84759
# Ricardo Martins 84761

# = = = =  T.A.D. coordenada  = = = = #
#                                     #
# Um elemento do tipo coordenada e'   #
# representado como um tuplo de dois  #
# elementos cujo primeiro elemento    #
# corresponde a linha e cujo segundo  #
# elemento corresponde a coluna.      #
#                                     #
# = = = = = = = = = = = = = = = = = = #

# Construtor:

def cria_coordenada(l, c):
    
    ''' cria_coordenada : int x int -> coordenada
cria_coordenada(l, c) cria uma coordenada correspondente ao par (l, c) '''
    
    if type(l) != int or type(c) != int or l <= 0 or c <= 0:
        
        raise ValueError('cria_coordenada: argumentos invalidos')
    
    else:
     
        return (l, c)

# Selectores:

def coordenada_linha(c):
    
    ''' coordenada_linha : coordenada -> int
coordenada_linha(c) devolve a linha correspondente a coordenada dada como 
argumento'''
        
    return c[0]

def coordenada_coluna(c):
    
    ''' coordenada_coluna : coordenada -> int
coordenada_coluna(c) devolve a coluna correspondente a coordenada dada 
como argumento'''
    
    return c[1]

# Reconhecedor:

def e_coordenada(c):
    
    ''' e_coordenada : universal -> logico
e_coordenada(arg) devolve True caso o argumento dado seja do tipo coordenada e 
False em caso contrario.'''

    if type(c) is tuple and len(c) == 2:
        
        return type(coordenada_linha(c)) is int and type(coordenada_coluna(c)) is int and coordenada_linha(c) > 0 and coordenada_coluna(c) > 0
    
    else:
        
        return False
    
# Teste:

def coordenadas_iguais(c1, c2):
    
    ''' coordenadas_iguais : coordenada x coordenada -> logico
coordenadas_iguais(c1, c2) devolve True caso c1 seja igual a c2 e False em caso 
contrario.'''    
    
    return c1 == c2

# Transformador:

def coordenada_para_cadeia(c):
    
    ''' coordenada_para_cadeia : coordenada -> cad. caracteres
coordenada_para_cadeia() devolve uma cadeia de carateres (linha : coluna)'''

    return '(' + str(coordenada_linha(c)) + ' ' + ':' + ' ' + str(coordenada_coluna(c)) + ')'

# = = = = = = T.A.D.  tabuleiro = = = = = = #
#                                           #
# Um tabuleiro e' representado como         #
# um tuplo com 2 elementos, o primeiro      #
# e' um tuplo de tuplos com as              #
# especificacoes do respectivo tabuleiro    #
# e o segundo e' uma lista de listas        #
# correspondente 'as linhas do tabuleiro    #
# de Picross.                               #
#                                           #
# = = = = = = = = = = = = = = = = = = = = = #

# Construtor:

def cria_tabuleiro(e):
    
    ''' cria_tabuleiro : tuplo -> tabuleiro
cria_tabuleiro() devolve um novo tabuleiro vazio com celulas a 0.'''    

    if type(e) is tuple and len(e) == 2 and len(e[0]) == len(e[1]) and verifica_elementos(e) and valida_especificacoes(e):
        
        return e, list([0,] * len(e[1]) for i in range(len(e[0])))

    else:
        
        raise ValueError ('cria_tabuleiro: argumentos invalidos')
        
               # tab[0] - linhas ; tab[1] - colunas
               # return especificacoes, tabuleiro

# Selectores:

def tabuleiro_dimensoes(tab):
    
    '''tabuleiro_dimensoes : tabuleiro -> tuple
tabuleiro_dimensoes() recebe como argumento um elemento tab do tipo tabuleiro
e devolve um tuplo com dois elementos, sendo o primeiro o numero de linhas e o
segundo o numero de colunas.'''
    
    return len(tabuleiro_especificacoes(tab)[0]), len(tabuleiro_especificacoes(tab)[1])

def tabuleiro_especificacoes(tab):
   
    '''tabuleiro_especificacoes : tabuleiro -> tuple
tabuleiro_especificacoes() recebe como argumento um elemento tab do tipo
tabuleiro e devolve o tuplo relativo as suas especificacoes'''
    
    return tab[0]

def tabuleiro_celula(tab, c):
    
    ''' tabuleiro_celula : tabuleiro x coordenada -> {0, 1, 2}
tabuleiro_celula() recebe como argumento um tabuleiro e uma coordenada, 
devolvendo o valor que consta na posicao dessa coordenada no tabuleiro dado.'''
    
    if e_coordenada(c) and e_tabuleiro(tab):
        
        if 1 <= coordenada_linha(c) <= tabuleiro_dimensoes(tab)[0] and 1 <= coordenada_coluna(c) <= tabuleiro_dimensoes(tab)[1]:
        
            return tab[1][coordenada_linha(c)-1][coordenada_coluna(c)-1]
        
        else:
            
            raise ValueError('tabuleiro_celula: argumentos invalidos')        
    else:
        
        raise ValueError('tabuleiro_celula: argumentos invalidos')
    
# Modificadores:    

def tabuleiro_preenche_celula(tab, c, valor):
    
    ''' tabuleiro_preenche_celula : tabuleiro x coordenada x int -> tabuleiro
tabuleiro(tab, c, v) coloca o valor v na celula correspondente a 
coordenada c do tabuleiro tab.'''
    
    if not e_tabuleiro(tab) or not e_coordenada(c) or type(valor) is not int:
        
        raise ValueError('tabuleiro_preenche_celula: argumentos invalidos')
    
    else:
        
        if coordenada_linha(c) > tabuleiro_dimensoes(tab)[0] or coordenada_coluna(c) > tabuleiro_dimensoes(tab)[1] or valor not in [0,1,2]:
            
            raise ValueError('tabuleiro_preenche_celula: argumentos invalidos')
        
        else:
            
            tab[1][coordenada_linha(c)-1][coordenada_coluna(c)-1] = valor
            
            return tab    
        
# Reconhecedores:

def e_tabuleiro(tab):
    
    ''' e_tabuleiro : universal -> logico
e_tabuleiro(tab) devolve True se o seu argumento for do tipo tabuleiro e False 
em caso contrario.'''    
    
    if type(tab) is not tuple:
        
        return False
            
    else:
        
        if type(tab) is tuple and len(tab) == 2 and type(tab[1]) is list:
            
            return tabuleiro_dimensoes(tab)[0] == tabuleiro_dimensoes(tab)[1]
        
        else:
            
            return False

def tabuleiro_completo(tab):
    
    linhas_col = transposta(tab)
    
    linhas_compl = 0
    
    for translinha in range(0, len(linhas_col)):
        
        for linha in range(0, len(tab[1])):
            
            if linha_completa(tabuleiro_especificacoes(tab)[1][translinha], linhas_col[translinha]) == True and linha_completa(tabuleiro_especificacoes(tab)[0][linha], tab[1][linha]) == True:
                
                linhas_compl += 1
        
        if linhas_compl == len(tab[1]):
        
            return True
    
        else:
        
            return False

# Funcoes Adicionais:

def tabuleiro_celulas_vazias(t):
    
    ''' tabuleiro_celulas_vazias : tabuleiro -> lista
tabuleiro_celulas_vazias(t) devolve uma lista que contem as coordenadas de todas 
as celulas vazias do tabuleiro t.'''
    
    lista = []
    
    for l in range(0, tabuleiro_dimensoes(t)[0]):
    
        for c in range(0, tabuleiro_dimensoes(t)[1]):
            
            if t[1][l][c] == 0:
                
                lista = lista + [cria_coordenada(l + 1, c + 1)]
                
    return lista

def linha_completa(espec, linha):
    
    return sum(espec) == sum(linha) - len(linha)

# Teste:
        
def tabuleiros_iguais(tab1, tab2):
    
    ''' tabuleiros_iguais : tabuleiro x tabuleiro -> logico
tabuleiros_iguais(tab1, tab2) devolve True caso tab1 seja igual a tab2 e 
False em caso contrario.'''
    
    if e_tabuleiro(tab1) and e_tabuleiro(tab2):
        
        return tab1 == tab2
    
    else:
        
        return False
    
# Transformador de Saida:    
    
def escreve_tabuleiro(tab):
    
    ''' escreve_tabuleiro : tabuleiro -> {}
escreve_tabuleiro(t) escreve para o ecra o tabuleiro de picross correspondente
ao argumento tab.'''    
    
    if not e_tabuleiro(tab):
        
        raise ValueError('escreve_tabuleiro: argumento invalido')
    
    else:    
        
        celulas_das_jogadas = tab[2:]    
        
        numero_de_linhas = tabuleiro_dimensoes(tab)[0]
        
        numero_de_colunas = tabuleiro_dimensoes(tab)[1]
        
        
        espec_col = tabuleiro_especificacoes(tab)[1]
        
        max_espec_col = max(espec_col, key = len)
        
        
        for i in range (len(max_espec_col) - 1 , -1, -1):
            
            res = ''
            
            for k in range (0, len(tabuleiro_especificacoes(tab)[1])):
                
                teste = tuple(reversed(tabuleiro_especificacoes(tab)[1][k]))
                
                if i + 1 <= len(tabuleiro_especificacoes(tab)[1][k]) :
                    
                    res = res + '  ' + str(teste[i]) + '  '
                
                else:
                    
                    res = res + '     '
            
            print (res + '  ')
            
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
        profundidade_horizontal_maxima = 0
        
        for i in range(0, tabuleiro_dimensoes(tab)[0]):
            
            if len(tabuleiro_especificacoes(tab)[0][i]) > profundidade_horizontal_maxima:
                
                profundidade_horizontal_maxima = len(tabuleiro_especificacoes(tab)[0][i])
       
        for linhas in range(0, tabuleiro_dimensoes(tab)[0]):        
            
            linha = ''         
            
            for colunas in range(0, len(tab[1][linhas])):
                    
                if tab[1][linhas][colunas] == 0:
                    
                    linha += ('[ ? ]')
                
                elif tab[1][linhas][colunas] == 1:
                    
                    linha += ('[ . ]')
                
                else:
                    
                    linha += ('[ x ]')  
                    
            pontos_negros_da_linha = tabuleiro_especificacoes(tab)[0][linhas]
            
            for pontos_negros_da_coordenada in (pontos_negros_da_linha):
                
                linha += ' ' + str(pontos_negros_da_coordenada)
                
            linha += calcula_espacos(len(pontos_negros_da_linha), profundidade_horizontal_maxima)  
            
            print (linha + '|')
        
        print('')

# = = = =  T.A.D. coordenada  = = = = #
#                                     #
# Um elemento do tipo jogada e'       #
# representado como um tuplo de dois  #
# elementos cujo primeiro elemento    #
# corresponde 'a coordenada e cujo    #
# segundo elemento corresponde ao     #  
# valor entre [0,1,2].                #
#                                     #
# = = = = = = = = = = = = = = = = = = #

# Construtor:

def cria_jogada(c, num):
    
    ''' cria_jogada : coordenada x {1, 2} -> jogada
cria_jogada() recebe como argumento uma coordenada e um inteiro correspondente
a 1 ou 2, criando um tuplo do tipo jogada'''
    
    if num not in [1,2] or type(c[0]) is not int or type(c[1]) is not int or type(num) is not int:
        
        raise ValueError('cria_jogada: argumentos invalidos')
    
    else:
        
        return c, num

# Selectores:

def jogada_coordenada(jog):
    
    ''' jogada_coordenada : jogada -> coordenada
jogada_coordenada() recebe como argumento um tuplo do tipo jogada e devolve a
coordenada respetiva. '''
    
    return jog[0]

def jogada_valor(jog):
    
    ''' jogada_valor : jogada -> {1,2}
jogada_coordenada() recebe como argumento um tuplo do tipo jogada e devolve o
valor respetivo. '''    
    
    return jog[1]

# Reconhecedor:

def e_jogada(jog):
    
    ''' e_jogada : universal -> logico
e_jogada() recebe como argumento um tuplo do tipo jogada e retorna a sua
validade. '''
    
    return type(jog) is tuple and type(jogada_coordenada(jog)) is tuple and type(jogada_valor(jog)) is int

# Teste:
    
def jogadas_iguais(jog, jog1):
    
    ''' jogadas_iguais : jogada x jogada -> logico
jogada '''
    
    return jog[0] == jog1[0] and jog[1] == jog1[1]

# Transformador:

def jogada_para_cadeia(jog):

    ''' jogada_para_cadeia : jogada -> cad. caracteres
jogada_para_cadeia() recebe como argumento um elemento do tipo jogada e retorna
uma cadeia de caracteres do tipo '(linha : coluna) --> valor' '''
    
    if type(jog[0]) is tuple and type(jog[1]) is int:
        
        return '(' + str(jog[0][0]) + ' ' + ':' + ' ' + str(jog[0][1]) + ')' + ' ' + '-->' + ' ' + str(jog[1])
    
# Funcoes Adicionais:

def le_tabuleiro(file):
    
    '''le_tabuleiro : str -> tuple
le_tabuleiro() acede a um ficheiro externo com as especificacoes de um jogo e
devolve um tuplo de dois tuplos com as especificacao das linhas e das colunas'''
    
    def abre_txt(file):
    
        return open(file, 'r')
    
    return eval(abre_txt(file).readline())

def pede_jogada(tab):
    
    ''' pede_jogada : tabuleiro x {} -> jogada
pede_jogada() pede ao utilizador para introduzir a jogada e retorna um elemento
do tipo jogada com os dados introduzidos pelo utilizador.'''    
    
    print('Introduza a jogada')
    
    c = str(input('- coordenada entre (1 : 1) e ' + '(' + str(len(tab[1])) + ' ' + ':' + ' ' + str(len(tab[1][0])) + ')' + ' >> '))
    
    v = str(input('- valor >> '))
    
    valor = eval(v)
    
    coordenada = (eval(c[1]), eval(c[5]))
    
    if (0 < coordenada[0] <= len(tab[1])) and (0 < coordenada[1] <= len(tab[1][0])):
        
        return cria_jogada(coordenada, valor)
    
    else:
        
        return False

def jogo_picross(file):

    ''' jogo_picross : {} -> {}
jogo_picross() permite jogar um jogo de picross.'''
    
    print('JOGO PICROSS')
    
    tab = cria_tabuleiro(le_tabuleiro(file))
    
    escreve_tabuleiro(tab)
    
    while tabuleiro_celulas_vazias(tab) != []:
    
        j = pede_jogada(tab)
        
        if j is not False:
    
            k = tabuleiro_preenche_celula(tab, j[0], j[1])
            
            escreve_tabuleiro(tab)        
        
        elif j is False:
            
            print('Jogada invalida.')
    
    if tabuleiro_completo(tab):
        
        #escreve_tabuleiro(tab)
        
        print('JOGO: Parabens, encontrou a solucao!')
        
        return tabuleiro_completo(tab)
    
    elif not tabuleiro_completo(tab):
        
        #escreve_tabuleiro(tab)
        
        print('JOGO: O tabuleiro nao esta correto!')
        
        return tabuleiro_completo(tab)
    
# = = = =  Funcoes Auxiliares  = = = = #

def retira_numeros(str):
    
    ''' retira_numeros : cad. carateres -> tuplo
retira_numeros() recebe como argumento uma cadeira de carateres e desta retira
os caracteres correspondentes as numeros inteiros, devolvidos num tuplo'''
    
    lst = list(filter(lambda x: (x) != '(' and x != ')' and x != ' ' and x != ':', list(str)))
    
    for i in range(0, len(lst)):
        
        lst[i] = int(lst[i])
    
    return tuple(lst)

def verifica_elementos(e):
    
    ''' verifica_elementos : tuplo -> tuplo
verifica_elementos() recebe como argumento um tuplo, junta todos os elementos
desse tuplo num tuplo e devolve, e' usada para transformar tuplo de tuplos num
tuplo apenas'''
    
    i=0 
    
    while i < len(e): 
        
        if isinstance(e[i], tuple): 
            
            e = e[:i] + e[i] + e[i+1:] 
        
        else: 
            
            i=i+1
        
    if all(isinstance(x, int) for x in e) and all(x >= 0 for x in e):
        
        return True
    
    else:
        
        return False

def calcula_espacos(profundidade_linha, profundidade_maxima):
    
    ''' calcula_espacos : int x int -> cad. caracteres
calcula_espacos() recebe como primeiro argumento o tamanho da especificacao de 
uma certa linha, e segundo o tamanho da maior especificacao de uma linha, sendo
que devolve uma cad. caracteres correspodente ao numero de espacos onde exibir
as especificacoes das linhas'''
    
    return str('  ' * (profundidade_maxima - profundidade_linha))

def valida_especificacoes(e):
    
    ''' valida_especificacoes : tuplo -> logico
valida_especificacoes() recebe como argumento um tuplo correspondente 'as 
especificacoes de um certo tabuleiro, e retorna a sua validade consoante a 
condicao imposta ((x, y, z) + 3 -1 < dimensao n)'''
    
    for i in range(0, 2):
                
        for j in range(0, len(e[0])):
                    
            res = sum(e[i][j]) + len(e[i][j]) - 1 <= len(e[0])  
            
            if not res:
                
                return False
    
    return True

def transposta(tab):
    ''' transposta : tabuleiro -> lista(colunas)
transposta() recebe um tabuleiro como argumento e devolve uma lista de
listas que correspondem 'as colunas deste.'''
    
    c = []

    for colunas in range(0, tabuleiro_dimensoes(tab)[1]):

        l = []

        for linhas in range(0, tabuleiro_dimensoes(tab)[0]):

            l.append(tab[1][linhas][colunas])

        c = c + [l]
        
    return c
