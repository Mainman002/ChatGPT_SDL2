# ChatGPT_SDL2
An SDL2 project generated mostly by ChatGPT (guided a lot by me fixing things though)

## Dependancies needed to run this projects
* gcc
* sdl2
* sdl2_image

![SDL_ChatGPT_Window](https://github.com/Mainman002/ChatGPT_SDL2/assets/11281480/d5e1f67a-4c53-4ba2-9409-9c2716c9276c)

If you're on macos then you can install using brew
```
brew install sdl2 sdl2_image
```
Thos files should be found in
```
/opt/homebrew/Cellar/sdl2/2.26.5/include
```
For simplicity I just coppied 
```
/opt/homebrew/Cellar/sdl2_image/2.6.3_1/include
```
into
```
/opt/homebrew/Cellar/sdl2/2.26.5/
```
Download the project
```
git clone https://github.com/Mainman002/ChatGPT_SDL2.git
```
Then open a terminal in the downloaded folder and run this to build the app
```
make
```
You can also clean the project with this command
```
make clean
```
