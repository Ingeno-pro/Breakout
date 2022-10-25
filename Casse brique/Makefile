breakout : main.o event.o levelmanager.o gui.o
	x86_64-w64-mingw32-gcc -o breakout.exe main.o event.o levelmanager.o gui.o `pkg-config --libs caca` 

main.o : src/main.c
	x86_64-w64-mingw32-gcc -o main.o -c src/main.c `pkg-config --libs caca` 

event.o : src/event.c
	x86_64-w64-mingw32-gcc -o event.o -c src/event.c `pkg-config --libs caca` 

levelmanager.o : src/level_manager.c
	x86_64-w64-mingw32-gcc -o levelmanager.o -c src/level_manager.c `pkg-config --libs caca` 
	
gui.o : src/gui.c
	x86_64-w64-mingw32-gcc -o gui.o -c src/gui.c `pkg-config --libs caca` 
