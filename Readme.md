# **Dining Philosophers Problem**

[![en](https://img.shields.io/badge/lang-en-red.svg)](README.md)
[![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.br.md)


[Program Logic](#program-logic)<br/>
[Results](#results)<br/>
[Execution](#execution)<br/>

<br/>

## Program Logic
The philosophers are executed in separate threads and all guarantees needed come from a monitor. It has a pointer to all necessary function and guarantees exclusive access to them.
The philosophers have a chance of changing states every clock (set by user). The program will end itself after a number of cicles or if it finds any problems.

<br/>

## Results
The code was executed without problems for 5.000.000 clock cicles.

<br/>

## Execution

```
    make run
```

<br/>

It's possible to change the clock and the chance of changing states with constants in the main.c file

```c
    const int CLOCK = 5000;
    const int MAX_CLOCK = 50000;
    const int CHANCE = 50;
```

The seeds are the same in every execution