# **Problema do Jantar dos Filósofos**

[![en](https://img.shields.io/badge/lang-en-red.svg)](README.md)
[![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.br.md)


[Relatório](#relatório)<br/>
[Lógica do programa](#lógica-do-programa)<br/>
[Resultados](#resultados)<br/>
[Execução](#execução)<br/>


## Relatório
[O relatório se encontra aqui](./doc/Relatório%20Filósofos%2011796847.pdf)

<br/>

## Lógica do programa
Os filósofos são executados em threads separadas e todas as garantias necessárias vêm de um monitor, que possui um ponteiro para todas as funções necessárias e garante acesso exclusivo à elas.
Os filósofos possuem uma chance de ação em todo clock (definido pelo usuário). As ações consistem em ficar com fome e terminar de comer dependendo do estado atual do filósofo.
O programa é encerrado após um número de ciclos de clock ou caso encontre erros de execução.

<br/>

## Resultados
O código foi executado sem conflitos por 5.000.000 ciclos de clock.

<br/>

## Execução

```
    make run
```

<br/>

É possível alterar o clock e a chance de ação pelas constantes em main.c

```c
    const int CLOCK = 5000;
    const int MAX_CLOCK = 50000;
    const int CHANCE = 50;
```

As seeds são as mesmas em toda execução