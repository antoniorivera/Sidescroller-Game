Sidescroller-Game
=================

Game written in C++ using SFML

Last Edited: September 29, 2014

UPDATE: I have added the level creator (it's a Java file that turns images into levels) and all the source code that I have so far. As mentioned, this game is still very early on in development. You can basically only walk around the level at this point. The one enemy was just added to test the movement and drawing logic; I haven't made collision detection for it yet. 

I, Antonio Rivera, am the sole creator of this game (not including SFML. SFML was created by Laurent Gomila. SFML is available for free use under the following license: http://sfml-dev.org/license.php). It is still in the early stages of development, and right now is more of an engine than a game. My goal with this game was to create efficient collision-detection and graphics engines. I also created a Java file that turns simple black-and-white images into levels to make the level editing/creating process much faster than with my other project. I will include the Java file (and probably the source code for everything) later.
Note that although there is one enemy present, I have not yet implemented player-enemy collision detection. All I have is player-world collision detection/correction, screen scrolling, and the level creator file (not currently included). 
To run the game, run "Sidescroller Game.exe". This version works only on Windows (I have not yet compiled a Linux version).

Controls
========

W - jump

A - move left

D - move right
