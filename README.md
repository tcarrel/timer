# Timer

A very simple timer with a display where the remaining time is easy for young children to understand.

![Setting the timer](https://raw.githubusercontent.com/tcarrel/timer/master/image/stopped.png)
Remaining time is very large and the time is very easy and quick to set using only the arrow keys.

![Timer Running](https://raw.githubusercontent.com/tcarrel/timer/master/image/running.png)
The amount of red decreases to the right as the timer runs giving young children and easy and quick way of judging the remaining
time.





I wrote a seperate program to convert image files into a c++ struct that can easily be converted to a surface (or texture) within SDL2.
I wanted to have as few files as possible other than the executable so compiling the images into the .exe worked well.  I chose this
method mostly as an experiment and to largely see it I could.  I suspect that the compiler is also doing some optimization on the files
in this form.  Using SDL_ttf to generate character sprites on the fly would be nice, but I cannot be completely certain that the font
I chose would be available where the program would be used and I wasn't sure of any licensing required for distributing fonts with my
program.  Although it's probably great for small images, like the one I use for the window icon, I would not really recommend using
this method for large images like I have here as it 1) necessitates the use of a [slower] 64-bit linker, 2) drastically increases the
size of the executable, however, include image files together with the program also does, so the trade-off is questionable, 3)
increases the compile time by a rediculous amount.  This only has a a few images and most of them need only keep their alpha channel,
so doing a similar thing for a large game with either hundreds or thousands of images, very large hd images, or both would become
prohibative really quickly.  [Packing the pixels as individual ints rather than having seperate character arrays for each color would
probably improve things, but I was in a slight hurry as I was initially working on this and wanted to keep it as simple as possible.]

A further 'improvement,' might be to compile SDL2 and it's functionality directly into my executable thereby making it completely
standalone.  Unfortunately, I'm not yet familiar enough with Visual Studio to be able to get this to work correctly, although I have
tried.  I also need to make sure it works well with multiple monitors but don't have a second monitor to test it with.
