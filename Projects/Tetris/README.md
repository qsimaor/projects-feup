# **LDTS_<13><5> - Tetris**

Tetris é um jogo simples que consiste em tentar fazer o número máximo de pontos através
do preenchimento de linhas com tetriminos, em que estes é possível movê-los, girá-los, fazê-los
descer mais rápido ou até mesmo "dropar". Conforme o nível aumenta através da pontuação, a queda das
peças também e, o jogo termina quando estas chegarem ao topo da tela.

O projeto foi desenvolvido por Rodrigo Ribeiro (up202108679@edu.fe.up.pt)
e Simão Rodrigues (up202005700@edu.fe.up.pt) para LDTS 2022⁄23.


## **Implemented Features**

**Rotação das peças:** O jogador através do "UP" consegue girar as peças. 

**Movimentação das peças:** O jogador através do "RIGHT" e do "LEFT" consegue mover as peças.

**Velocidade da peça:** A velocidade das peças pode ser aumentada com o "DOWN".

**Drop instantâneo:** O jogador através do "SPACE" consegue descer a peça instantâneamente.

**Ver as próximas peças:** É possível visualizar o formato das próximas peças no decorrer do jogo.

**Completar linhas:** Sempre que uma linha é completada, esta desaparece e as de cimas ocupam a sua posição.

**Pontuação:** Sempre que uma linha é completada, a pontuação aumenta em que, esta é calculado através
da multiplicação do seu valor base e nível.

**Nível:** Conforme a pontuação aumenta, por consequência o nível e a velocidade das peças aumenta também.

**Game over:** Quando as peças chegam ao topo da tela o jogador perde o jogo.

**Jogar novamente:** Sempre que o jogador perde o jogo tem a possibilidade de recomeçar.

**Menu:** Ao iniciar o programa, é exibido 3 opções ao jogador: o "Jogar", a visualização dos "Controlos" e "Sair".

**Jogar:** O jogador começa o jogo.

**Controlos:** O jogador acessa os controlos do jogo.

**Sair:** O jogador retira-se do jogo.

![tetris](https://user-images.githubusercontent.com/113983743/208766450-a4bbd31c-a0eb-45cc-b5dd-e48bc3dab8ec.png)
![giphy](https://user-images.githubusercontent.com/93003716/208778180-82f76e5e-883b-48d2-920c-6a7697592936.gif)


## **Planned Features**

Uma feature que achamos interessante de criar e que só nos apercebemos no final do projeto, foi a criação de um High Score. 


## **Design**

> Pattern: Model-View-Controller (MVC)

**Problema no contexto:** Separamos as responsabilidades do model, view e controller tornando-os
independentes para uma melhor organização do código.

**Pattern:**
- [Model](https://github.com/qsimaor/projects/tree/main/Tetris/src/main/java/tetris/Model): Representa a data.
- [View](https://github.com/qsimaor/projects/tree/main/Tetris/src/main/java/tetris/View): Envia as ações do jogador.
- [Controller](https://github.com/qsimaor/projects/tree/main/Tetris/src/main/java/tetris/Controller): Interpreta as ações do jogador.

**Implementação:**

![geral drawio](https://user-images.githubusercontent.com/93003716/207922450-59ae4a46-8cfb-4919-a8d0-9e951d2f3208.png)

**Consequências:** Código mais fácil de alterar, melhor testado.


> Pattern: Composite pattern

**Problema no contexto:** Vários objetos diferentes partilham os mesmo atributos e métodos.

**1) Pattern:**

- [Peça](https://github.com/qsimaor/projects/blob/main/Tetris/src/main/java/tetris/Model/Pecas/Peca.java): Contém todos os atributos e métodos de uma peça.
- [Peças](https://github.com/qsimaor/projects/tree/main/Tetris/src/main/java/tetris/Model/Pecas): As várias peças com extensões.

**Implementação:**

![pecas drawio](https://user-images.githubusercontent.com/93003716/207922588-7049f8a3-aeea-4c69-981d-a8c82722bcd9.png)


**2) Pattern:**

- [Menu](https://github.com/qsimaor/projects/blob/main/Tetris/src/main/java/tetris/Controller/Menus/Menu.java): Contém todos os atributos e métodos de um menu.
- [Menus](https://github.com/qsimaor/projects/tree/main/Tetris/src/main/java/tetris/Controller/Menus): Os vários menus com extensões.

**Implementação:**

![menus drawio](https://user-images.githubusercontent.com/93003716/207922623-e67bab30-3e86-406c-a78c-64615b1625f2.png)

**Consequências:** Classes diferentes com características idêndicas, sem a necessedidade de repetir código.


## **Known Code Smells** 

**Long Method**

Com o objetivo de resolver grande quantidade de linhas, criou-se um método que passa a chamar outros métodos, como o verificarDireita, verificarEsquerda e verificarBaixo chamados pelo método verificar, dentro da classe Peca.


## **Refactoring Suggestion**

**Large Class**

A classe Jogo por conter vários métodos, torna-se uma classe extensa, o que não achamos que deveríamos dividir esta classe, visto que é a classe principal e precisa de guardar uma grande quantidade de dados e diversos métodos para implementar a interface do jogo.

**Switch Statements**

Para simplificar os caminhos ao longo do programa, utilizamos os switch/ifs e, apesar de serem utilizadas em diferentes classes, estas foram feitas de forma simples, não existindo, razões para alterar.


## **Data Class**

Não existe nenhuma classe que não contenha métodos próprios.


## **Testing**

- Screenshot of coverage report

<img width="353" alt="image" src="https://user-images.githubusercontent.com/93003716/208681177-5f889599-615b-4afc-93cb-bb9e3a46498d.png">


## **Self-Evaluation**

- Rodrigo Ribeiro: 50%
- Simão Rodrigues: 50%
