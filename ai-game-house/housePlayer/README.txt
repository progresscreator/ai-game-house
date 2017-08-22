Atropos AI Project
Goals

The purpose of this project is to design a basic strategy for playing the Atropos game. I seek to implement an algorithm which shows success in beating human and random-move scripted players. Specifically, this project has three main goals: 

I. Design a Static Evaluator
Static Evaluators, also known as heuristic evaluation functions, can be used by game-playing programs to estimate the value of a board position. 

II. Select a Suitable Adversarial Search Algorithm
I selected the Alpha-Beta Pruning Algorithm as a suitable method for performing adversarial search in my AI player. 

III. Implement Chosen Algorithm to Play Atropos
I implemented my AI player to make decisions about Atropos board positions using my Static Evaluator and Alpha-Beta Pruning methods. I tested the effectiveness of my player in beating random and human players, and provide player results and smyce code below. 


Main Code

The three goals of this project are met using the files described below. These files are extensively commented to provide information on program functioning at key points in my AI system's reasoning process.

LastMove.h - Header file for LastMove object. LastMove parses an input string and stores it as the previous move performed in an Atropos game. Color and X, Y, Z coordinates are stored here. 

LastMove.cpp - CPP file for LastMove object. LastMove parses an input string and stores it as the previous move performed in an Atropos game. Color and X, Y, Z coordinates are stored here. 

GameBoard.h - Header file for GameBoard object. GameBoard reads in and stores a previous Atropos game state, and performs reasoning based on this stored state. Alpha-Beta, move scoring, and strategic analysis are performed within GameBoard. 

GameBoard.cpp - CPP file for GameBoard object. GameBoard reads in and stores a previous Atropos game state, and performs reasoning based on this stored state. Alpha-Beta, move scoring, and strategic analysis are performed within GameBoard. 

housePlayer.cpp - compiles to housePlayer.exe. This is the main player class for the project; calls to parse and store the input string and input board state within LastMove and GameBoard are performed here. Reasoning methods are called once an input string has been parsed, and output functions within housePlayer write the chosen next move to the console. 
Usage: housePlayer.exe [Input String] 


Performance

My program performs well in utilizing the Alpha-Beta filter as an adversarial search algorithm, winning 6 out of 10 games played against a random sampling of human players (n=20).


Compiled with Visual Studio 2008.

