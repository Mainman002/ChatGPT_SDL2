# ChatGPT_SDL2
An SDL2 project generated mostly by ChatGPT (guided a lot by me fixing things though)

## Dependancies needed to run this projects
* gcc
* sdl2
* sdl2_image

![Screenshot 2023-06-02 at 7 45 20 PM](https://github.com/Mainman002/ChatGPT_SDL2/assets/11281480/8f89013b-ed68-47e5-80e1-0d4d41de9a55)

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
make macos
```
```
make windows
```
```
make linux
```
You can run the app by running 1 of these commands
```
make run-macos
```
```
make run-windows
```
```
make run-linux
```
You can also clean the project with this command
```
make clean
```
