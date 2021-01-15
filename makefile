
clean:
	rm -rf *.o 

debug:
	make clean
	@echo
	@echo "---------- Building Debug Game ----------"
	@echo
	g++ -c src/*.cpp -std=c++14 -m64 -g -Wall -I include && g++ *.o -o bin/debug/main -I/usr/include/ -I/usr/local/include/ -lSDL2 -lSDL2_image -lSDL2_mixer
	@echo
	@echo "---------- Build Done ----------"
	@echo
	@echo "Now run the game with command 'make run'"
	@echo

run:
	./bin/debug/main
