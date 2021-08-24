# Battleshipp

This project was for the purpose of learning C++. You can find some notes about what I learned in `learned.txt` The program is capable of letting either a human or computer play against randomly placed ships.

## The Strategy
The default computer player chooses a random square that has not yet been hit. There is another strategy included which, to my knowledge, is the best possible battleship strategy.

The strategy is an implementation of an amazing write-up done by [DataGenetics](https://www.datagenetics.com/blog/december32011/)




![battleshipfast](https://user-images.githubusercontent.com/35354196/130553440-ef5f03fc-3da0-486d-8f02-17af0aea79c0.gif)

<p style="font-size:11px">Visual example of the strategy</p>



## Installation
To run this program yourself, simply download the project and run the included makefile.

Note that the default makefile produces an executable which runs the computer strategy for 100 games.

The program can be compiled and run using the command
```sh
make && bin/CPUstrat
```
