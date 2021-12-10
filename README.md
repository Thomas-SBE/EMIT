<p align='center'>
   <img src='https://github.com/Thomas-SBE/EMIT/blob/main/emitlogo.png?raw=true' alt="EMIT Official Logo"/>
</p>

<p align='center'>
  <img src='https://img.shields.io/badge/Languages%20:-C%20%2F%20C%2B%2B-blueviolet' alt="Language C C++"/>
  <img src='https://img.shields.io/badge/Platforms%20:-UNIX--based-informational' alt="UNIX based"/>
  <img src='https://img.shields.io/github/last-commit/Thomas-SBE/EMIT?color=success&label=Last%20Commit%20%3A&logo=github' alt="Last commit"/>
  <img src='https://img.shields.io/github/workflow/status/Thomas-SBE/EMIT/c-cpp?label=Last%20Build%20Status%20%3A&logo=github' alt="Last build pass"/>
  <br/>
  <img src='https://img.shields.io/badge/Current%20Implementations%20Stage%20%3A-Stage%201%20%3A%20Static%20Canvas%20Display-blueviolet' alt="Last build pass"/>
</p>

**EMIT** or *Extended & More Interactive Terminal* library is for **C++** program makers who wants a little more from their terminal outputs. From displaying graphs, graphical user interfaces or simple imagery, EMIT allows you to make *buffers* that can be drawn on, and then rendered to the terminal. Combined with the *EMIT Window* which makes buffers *"refresh-able"* you can dynamize your terminal to your needs !

# Development Stages :

I am currently following a roadmap for this project, each feature will be implemented once the previous one has been complete and estimated stable.
There will be several development stages, which will be listed below. *The current status can also be seen on the top of the [README](README.md).

## <img src="https://cdn-icons-png.flaticon.com/32/554/554099.png"/> Stage 1 : Static Canvas Display

- [x] Making **buffers** to store canvas data to be drawn on, released upon deletion of the *EMITBuffer* object.
- [x] Drawing **char** into the buffer at specified **EMITPoint** positions.
- [x] Defining **EMITRect** to represent a rectangular structure, made from 2 *EMITPoint*.
- [x] Implementing functions to draw rectangles from given *EMITRect* positions & dimensions.
- [x] Implementing the creation of **text areas** which contains paragraphs of text.
- [x] Updating *text areas* to allow **word-breaking** instead of **char-breaking** in words at the edge of the area. 
- [x] Implementing function to draw **lines** into the buffer ( thanks to the [*Bresenham's line algorithm*](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm) ).
- [x] Drawing **strings** ( aka. *const char\** ) into the *buffer*, width overflow will char-break the word and continue on the next line.
- [x] Implemented **EMITColor** object, to represent a simple terminal colorization and text decoration with different **bitwise flags**.

## <img src="https://cdn-icons-png.flaticon.com/32/453/453584.png"/> Stage 2 : Buffer Utilities

*This stage is not fully established yet !* However, here are some heads up on what you can expect in **Stage 2** !

- Text alignment, text justification.
- Allowing custom colors for users with a 256 colors terminal.
- More *"Elements"*, for GUI purposes.
- More buffer *"types"*, for instance an *EMITGraph* to display data visually.
- A start in the dynamic canvas rendering, proper ways to clear terminals ( *efficient ways* ).
- And much more ...

## <img src="https://cdn-icons-png.flaticon.com/32/2920/2920100.png"/> *Stage 3*

*This stage is currently in the thinkings !* But, it should be related to the buffer refreshing, and some more GUI stuff !

# Feedback

All versions pushed to this repository should have no memory leaks, however if you encounter any error ( *including memory leaks* ) feel free to report it with the issues tab with the maximum amount of details possible. 
> All leaks are checked using [valgrind](https://fr.wikipedia.org/wiki/Valgrind) with the `--leak-check=full` flag.



<p align="right">
  <sub><sub>All rights for the icons used on stages' descriptions go to: <a href="https://www.flaticon.com/">Flaticon</a>.</sub></sub>
</p>
