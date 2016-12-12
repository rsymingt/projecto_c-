all: clear projecto run
	
projecto: src/*.cpp
	g++ src/*.cpp -Iinclude -o projecto
	
run:
	./projecto
	
clean:
	rm main
	
clear:
	clear