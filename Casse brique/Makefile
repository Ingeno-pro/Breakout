breakout : main.o event.o levelmanager.o gui.o
	gcc -o breakout main.o event.o levelmanager.o gui.o `pkg-config --libs caca` 

main.o : src/main.c
	gcc -o main.o -c src/main.c `pkg-config --libs caca` 

event.o : src/event.c
	gcc -o event.o -c src/event.c `pkg-config --libs caca` 

levelmanager.o : src/level_manager.c
	gcc -o levelmanager.o -c src/level_manager.c `pkg-config --libs caca` 
	
gui.o : src/gui.c
	gcc -o gui.o -c src/gui.c `pkg-config --libs caca` 
