# Grupo 028
# TagusPark

# Ricardo Martins 84761
# Ricardo Oliveira 84759


#-------------------------------Recursos---------------------------------------#


Partidos = (("Partido Democratico Republicano", "PDR"),\
("CDU - Coligacao Democratica Unitaria", "PCP-PEV"),\
("Portugal a Frente", "PPD/PSD-CDS/PP"),\
("Partido da Terra", "MPT"),("LIVRE/Tempo de Avancar","L/TDA"),\
("Pessoas-Animais-Natureza", "PAN"),("Agir", "PTP-MAS"),\
("Juntos pelo Povo","JPP"),("Partido Nacional Renovador", "PNR"),\
("Partido Popular Monarquico", "PPM"),("Nos, Cidadaos!", "NC"),\
("Partido Comunista dos Trabalhadores Portugueses", "PCTP/MRPP"),\
("Partido Socialista", "PS"),("Bloco de Esquerda", "B.E."),\
("Partido Unido dos Reformados e Pensionistas","PURP"))          


#------------------------------------------------------------------------------#
#                                                                              #
#-----------------------------Funcoes Principais-------------------------------#
#                                                                              #
#------------------------------------------------------------------------------#


def mandatos(nr_mandatos, nr_votos): 
    
    ''' mandatos : ((int), (tuple)) -> (tuple)
    Cria lista de deputados eleitos a nivel de circulo eleitoral atraves do 
    metodo dhondt, com o nr mandatos (int) e de votos recebidos (tuple) '''
    
    deputados_eleitos = list((0,) * len(nr_votos))  
    # Criacao da lista base ondefica a distribuicao de mandatos
    
    l_nr_votos = list(nr_votos)
    
    while nr_mandatos > 0:
        
        x = parametros(l_nr_votos) 
        # Utilizando a funcao auxiliar, traz a lista com os indices 
        # dos maiores valores
 
        f = x[0]  
        # Descobre o indice dos deputados eleitos ao qual se acrescenta 
        # um mandato            
        
        for k in x:
            
            if  deputados_eleitos[k] < deputados_eleitos[f]:
                
                f = k 
       
        deputados_eleitos[f] = deputados_eleitos[f] + 1  
        # Adiciona um deputado na lista dos deputados eleitos
        # na posicao de indice f
        
        divisor = deputados_eleitos[f] + 1  # Prepara o divisor 
                
        l_nr_votos[f] = nr_votos[f] / divisor  # Atualizacao da lista l_nr_votos
        
        nr_mandatos = nr_mandatos - 1  # Decrementacao dos numeros de mandatos
    
    return tuple(deputados_eleitos)

#------------------------------Fim: mandatos-----------------------------------#

def assembleia(votacoes):
    
    ''' assembleia : (tuple) -> (tuple)
    Distribui mandatos a cada candidatura a nivel nacional, em forma tuple,
    com recurso a funcao mandatos para distribuir mandatos por todos
    os circulos eleitorais '''
    
    nr_mandatos = (16, 3, 19, 3, 4, 9, 3, 9, 4, 10, 47, \
                   2, 39, 9, 18, 6, 5, 9, 5, 6, 2, 2)  
    # Numero mandatos por circulo eleitoral
    
    nr_partidos = len(Partidos)
    
    total_mandatos = list((0,)* nr_partidos) 
    # Criacao lista base para adicionar total de mandatos 
    # distribuidos a cada candidatura
    
    for i in range(0, len(nr_mandatos)):
    
        dist_mandatos = mandatos(nr_mandatos[i], votacoes[i]) 
        # Recurso a funcao mandatos
        
        for k in range(0, nr_partidos):

            total_mandatos[k] = total_mandatos[k] + dist_mandatos[k]
                
    return  tuple(total_mandatos) 
# Lista da distribuicao de mandatos a nivel nacional

#------------------------------Fim: assembleia---------------------------------#
    
def max_mandatos(votacoes):
    
    ''' max_mandatos : (tuple) -> (tuple)
    Tem por base um tuplo de votacoes em todos os circulos eleitorais e 
    devolve o partido que teve mais mandatos atribuidos a nivel nacional'''

    maxvotos_candidatura = parametros(assembleia(votacoes)) 
    # Recurso a funcao auxiliar
    
    if len(maxvotos_candidatura) > 1:
        
        return "Empate tecnico"
   
    else: 
        
        partido_vencedor = Partidos[maxvotos_candidatura[0]] 
        # Recorre ao recurso partidos dado inicialmente e escolhe o partido

        return (partido_vencedor[1] + '\t' + partido_vencedor[0])


#------------------------------------------------------------------------------#
#                                                                              #
#------------------------------Funcao Auxiliar---------------------------------#
#                                                                              #
#------------------------------------------------------------------------------#


def parametros(l_nr_votos): 
    
    ''' parametro : (list) -> (list) 
    Devolve o indice dos maximos de um tuplo fornecido '''
    
    maximos = list()
    
    max_nr_votos = max(l_nr_votos)
    
    for i in range(0, len(l_nr_votos)):
        
        if l_nr_votos[i] == max_nr_votos:
            
            maximos.append(i)    

    return (maximos)

#---------------------------Fim: parametros------------------------------------#
