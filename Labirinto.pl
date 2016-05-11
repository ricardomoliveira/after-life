% PROJETO DE LOGICA PARA PROGRAMACAO: LABIRINTOS.

% Ricardo de Oliveira, 84759.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Codigo %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Predicados Principais %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% Predicado distancia(Coord1:tuple, Coord2:tuple, ?-Dist:int)
% Distancia representa a distancia entre as duas coordenadas dadas.

distancia((L1, C1), (L2, C2), Dist) :-
    Dist is abs(L1-L2) + abs(C1-C2).

%% Predicado movs_possiveis(Lab:list, Pos:tuple, Movs:list, ?-Poss: list)
% Considerando a posicao atual, devolve os Movimentos Possiveis no labirinto, cumprindo o criterio de nao
% visitar a mesma posicao mais que uma vez e seguindo a ordem de movimentos {cima, baixo, esquerda, direita},
% com o auxilio do predicado get_celula/3, move/4 e apaga_elemento/3.

movs_possiveis(Lab, (X,Y), Movs, Poss) :-
    get_celula(Lab, (X,Y), Celula),
    move((X,Y), Celula, C, Movs, c),         % Movimento 'c' move o jogador para cima
    move((X,Y), Celula, B, Movs, b),         % Movimento 'b' move o jogador para baixo
    move((X,Y), Celula, E, Movs, e),         % Movimento 'e' move o jogador para a esquerda
    move((X,Y), Celula, D, Movs, d),         % Movimento 'd' move o jogador para a direita
    delete([C, B, E, D], [], Poss), !.       % Retira as entradas dos movimentos impossiveis de realizar

%% Predicado ordena_poss(Lista:list, ?-Poss:list, Pos_inicial:tuple, Pos_final:tuple)
% Tendo em conta a lista de movimentos possiveis obtidos pelo predicado movs_possiveis, faz a sua ordenacao
% em relacao a menor distancia a Posicao Final, e em caso de igualdade, em relacao a maior distancia a
% Posicao Inicial, com o auxilio do predicado ordenada_coordenadas/6, sendo Possiveis a lista ordenada.

ordena_poss(Lista, Poss, Pos_inicial, Pos_final) :-
    length(Lista, 1),                                                   % Se o tamanho da lista de movimentos tiver um elemento
    Poss = Lista;                                                       % Devolve a lista porque nao ha comparacoes

    length(Lista, 2),                                                   % Se o tamanho da lista de movimentos tiver dois elementos
    ordena_coordenadas(Lista, 0, 1, Pos_final, Pos_inicial, Poss), !;   % Compara o primeiro e o segundo elemento

    length(Lista, 3),                                                   % Se o tamanho da lista de movimentos tiver tres elementos
    ordena_coordenadas(Lista, 0, 1, Pos_final, Pos_inicial, Poss1),     % Compara o primeiro e o segundo elemento
    ordena_coordenadas(Poss1, 0, 2, Pos_final, Pos_inicial, Poss2),     % Compara o primeiro e o terceiro elemento
    ordena_coordenadas(Poss2, 1, 2, Pos_final, Pos_inicial, Poss), !;   % Compara o segundo e o terceiro elemento

    length(Lista, 4),                                                   % Se o tamanho da lista de movimentos tiver quatro elementos
    ordena_coordenadas(Lista, 0, 1, Pos_final, Pos_inicial, Poss1),     % Compara o primeiro e o segundo elemento
    ordena_coordenadas(Poss1, 0, 2, Pos_final, Pos_inicial, Poss2),     % Compara o primeiro e o terceiro elemento
    ordena_coordenadas(Poss2, 0, 3, Pos_final, Pos_inicial, Poss3),     % Compara o primeiro e o quatro elemento
    ordena_coordenadas(Poss3, 1, 2, Pos_final, Pos_inicial, Poss4),     % Compara o segundo e o terceiro elemento
    ordena_coordenadas(Poss4, 1, 3, Pos_final, Pos_inicial, Poss5),     % Compara o segundo e o terceiro elemento
    ordena_coordenadas(Poss5, 2, 3, Pos_final, Pos_inicial, Poss), !.   % Compara o terceiro e o quatro elemento

%% Predicado resolve1(Lab:list, Pos_inicial:tuple, Pos_final:tuple, ?-Movs:list)
% Devolve, em Movimentos, a lista de movimentos a partir da Posicao Inicial ate alcancar
% a Posicao Final, obedecendo a restricao de nao visitar as celulas mais do que uma vez,
% recorrendo ao auxilio do predicado movs_possiveis/4.

resolve1(Lab, (X,Y), Pos_final, Movs) :-                     % Caso geral
    resolve1(Lab, (X,Y), Pos_final, [(i, X, Y)], Movs),!.    % Inicia a lista de movimentos com a posicao inicial

resolve1(_, Pos_final, Pos_final, Movs, Movs):- !.           % Caso de Paragem: Quando a posicao atual e igual a posicao final

resolve1(Lab, (X,Y), Pos_final, Mov_old, Movs) :-
    movs_possiveis(Lab, (X,Y), Mov_old, Possiveis),!,        % Fornece os movimentos possiveis a partir da posicao dada
    member(Next, Possiveis),                                 % Retira o primeiro movimento possivel
    append(Mov_old, [Next], Mov_old1),                       % Junta esse movimento à lista de movimentos efetuados
    get_coordenadas(Next, (X1, Y1)),                         % Retira as coodenadas do movimento realizado
    resolve1(Lab, (X1, Y1), Pos_final, Mov_old1, Movs).      % Chama o predicado com a nova posicao

%% Predicado resolve2(Lab:list, Pos_inicial:tuple, Pos_final:tuple, ?-Movs:list)
% Fornece em Movimentos a lista de movimentos a efetuar desde a Posicao Inicial ate a Posicao Final
% tendo em conta os movimentos possiveis ordenados, recorrendo ao auxilio dos predicados movs_possiveis/4
% e ordena_poss/4, de forma a obter uma solucao mais certa em relacao a fornecida pelo predicado resolve1/4.

resolve2(Lab, (X,Y), Pos_final, Movs) :-                                    % Caso geral
    resolve2(Lab, (X,Y), Pos_final, Movs, [(i, X, Y)], (X,Y)), !.           % Inicia a lista de movimentos com a posicao inicial e preserva numa variavel a posicao inicial

resolve2(_, Pos_final, Pos_final, Movs, Movs, _).                           % Caso de Paragem: Quando a posicao atual e igual a posicao final

resolve2(Lab, (X,Y), Pos_final, Movs, Mov_old, Pos_inicial) :-
    movs_possiveis(Lab, (X,Y), Mov_old, Possiveis),                         % Fornece os movimentos possiveis a partir da posicao
    ordena_poss(Possiveis, Poss, Pos_inicial, Pos_final), !,                % Ordena os movimentos possiveis obtidos
    member(Next, Poss),                                                     % Retira o primeiro movimento possivel
    append(Mov_old, [Next], Mov_old1),                                      % Junta o elemento aos movimentos ja efetuados
    get_coordenadas(Next, (X1, Y1)),                                        % Retira as coordenadas do movimento efetuado
    resolve2(Lab, (X1, Y1), Pos_final, Movs, Mov_old1, Pos_inicial).        % Chama o predicado com a nova posicao

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Predicados Auxiliares %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% Facto get_coordenadas(Celula:tuple, ?-Coord:tuple)
% Dada uma posicao inicial com as coordenadas e o movimento realizado posteriormente, retira as
% coordenadas (X,Y).

get_coordenadas((_,X,Y), (X,Y)).

%% Predicado get_celula(Lab:list, Coord:tuple, ?-Celula:list)
% Procura no labirinto fornecido a linha e coluna correspondente as coordenadas dadas, retornando a celula
% obtida em Celula.

get_celula(Lab, (X,Y), Celula) :-
    nth1(X, Lab, Linha), nth1(Y, Linha, Celula).

%% Predicado troca_elementos(Lista:list, Elem1:tuple, Elem2:tuple, ?-ListaFinal:list)
% Procura na Lista fornecida o Elem1 e o Elem2, preservando as entradas anteriores ao Elem1 e
% anteriores ao Elem2, desta forma, recorrendo a uma lista temporária, consegue trocar as entradas dos
% Elementos dados na Lista fornecida, sem perder dados, retornando a ListaFinal com as trocas realizadas.

troca_elementos(Lista, Elem1, Elem2, AltLista) :-
    same_length(Lista, AltLista),
    append(AntesElem1, [EmElem1|DepoisElem1], Lista),
    append(AntesElem1, [EmElem2|DepoisElem1], AuxLista),
    append(AntesElem2, [EmElem2|DepoisElem2], AuxLista),
    append(AntesElem2, [EmElem1|DepoisElem2], AltLista),
    length(AntesElem1, Elem1),
    length(AntesElem2, Elem2).

%% Predicado move(PosAtual:tuple, Celula:list, ?-Mov:tuple, Movs:list, Direcao:char)
% Verifica se o movimento e possivel, ou seja, se a letra correspondente nao se encontra na celula correspondente a posicao atual
% e ainda se a coordenada nova que esse movimento originaria nao esta presente na lista de movimentos ja efetuados, respeitando a
% restricao de so visitar cada celula uma vez. Verificando estas duas condicoes, altera as coordenadas, nao verificando, retorna uma
% lista vazia, que vai ser posteriormente eliminada. Predicado Auxiliar de movs_possiveis/4.

move((X,Y), Celula, X1, Movs, c) :-             % Caso Particular: Realiza o movimento para cima
    not(member(c, Celula)),                     % Verifica se a posicao atual nao tem uma parede em cima
    XZ is X - 1, X1 = (c, XZ, Y),               % Fornece as coordenadas da posicao em que vai ficar se o movimento for efetuado
    not(member((_, XZ, Y), Movs));              % Verifica se a posicao para onde se iria mover nao foi visitada previamente
    X1 = [].                                    % Caso de Falha: Fornece uma lista vazia que vai ser apagada depois

move((X,Y), Celula, X1, Movs, b) :-             % Caso Particular: Realiza o movimento para baixo
    not(member(b, Celula)),                     % Verifica se a posicao atual nao tem uma parede em baixo
    X1 = (b, XZ, Y), succ(X, XZ),               % Fornece as coordenadas da posicao em que vai ficar se o movimento for efetuado
    not(member((_, XZ, Y), Movs));              % Verifica se a posicao para onde se iria mover nao foi visitada previamente
    X1 = [].                                    % Caso de Falha: Fornece uma lista vazia que vai ser apagada depois

move((X,Y), Celula, Y1, Movs, e) :-             % Caso Particular: Realiza o movimento para a esquerda
    not(member(e, Celula)),                     % Verifica se a posicao atual nao tem uma parede a esquerda
    Y1 = (e, X, YZ), YZ is Y - 1,               % Fornece as coordenadas da posicao em que vai ficar se o movimento for efetuado
    not(member((_, X, YZ), Movs));              % Verifica se a posicao para onde se iria mover nao foi visitada previamente
    Y1 = [].                                    % Caso de Falha: Fornece uma lista vazia que vai ser apagada depois

move((X,Y), Celula, Y1, Movs, d) :-             % Caso Particular: Realiza o movimento para a direita
    not(member(d, Celula)),                     % Verifica se a posicao atual nao tem uma parede a direita
    Y1 = (d, X, YZ), succ(Y, YZ),               % Fornece as coordenadas da posicao em que vai ficar se o movimento for efetuado
    not(member((_, X, YZ), Movs));              % Verifica se a posicao para onde se iria mover nao foi visitada previamente
    Y1 = [].                                    % Caso de Falha: Fornece uma lista vazia que vai ser apagada depois

%% Predicado ordena_coordenadas(Lista:list, Elem1:tuple, Elem2:tuple, PosFinal:tuple, PosInicial:tuple, ?-ListaOrdenada:list)
% Organiza os elementos de uma dada Lista, dois a dois, em relacao as posicoes finais e iniciais dadas, recorrendo
% ao predicado distancia/3, por fim retornando a Lista Ordenada. Predicado Auxiliar de ordena_poss/4.

ordena_coordenadas(Lista, Pos1, Pos2, Pos_final, Pos_inicial, Lista_final) :-

    (nth0(Pos1, Lista, (_,X1,Y1)),                  % Retira o elemento da Pos1 da Lista dada
    nth0(Pos2, Lista, (_,X2, Y2)),                  % Retira o elemento da Pos2 da Lista dada
    distancia((X1,Y1), Pos_inicial, Disti1),        % Fornece a distancia entre o primeiro elemento e a posicao inicial
    distancia((X2,Y2), Pos_inicial, Disti2),        % Fornece a distancia entre o segundo elemento e a posicao inicial
    distancia((X1,Y1), Pos_final, Distf1),          % Fornece a distancia entre o primeiro elemento e a posicao Final
    distancia((X2,Y2), Pos_final, Distf2),          % Fornece a distancia entre o segundo elemento e a posicao Final

    (
        Distf1 == Distf2, Disti1 < Disti2; Distf1 > Distf2  % Condicoes em que ocorre a troca de elementos
    )
    ->
        troca_elementos(Lista, Pos1, Pos2, Lista_final)     % Os dois elementos sao trocados de ordem
    );
        Lista_final = Lista.                            % Caso de Falha: A lista ja esta ordenada

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Fim de Codigo %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
