# bingo-simulator
Bingo Simulator for real-world testing

The inspiration for this project comes from being on a Disney cruise.
On board, they host bingo games, where on the last game you play crossout bingo.
They advertise that if you win in 45 moves or less, you get a $5,000 prize.
I tried researching into it, but because of my lack of math expertise once we have issues like the free space, I chose to brute force testing it instead.

This project is entirely in C++, and is primarily meant to emulate creating random bingo cards, playing the game, and seeing how many moves it took to complete.
It is able to run on a variable number of threads and is not based on OS-dependent time for random number generation.

## Running the project:
Included is a makefile, readme (obviously), and src folder with source code \
There is nothing unusual, here it is anyway:
1. Ensure you have GCC (g++) / MingW32 (Windows) installed
2. Navigate to the folder in your terminal of choice
3. Run ```make br(number)``` on Unix systems, or ```MinGW32-make br(number)w``` if on Windows
4. Enjoy

It is optimal to spawn as many threads as your processor has.

Nearly as optimal is to simply put as many cores, however all current AMD and Intel processors have hyperthreading that can get a bit more performance out of the same number of cores.

If you are unaware of what you have (and are on Windows), just check task manager -> performance -> CPU and put in the number of Logical Processors your chip has.
