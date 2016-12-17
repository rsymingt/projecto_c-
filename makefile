all: clear projecto run

projecto: src/*.cpp include/*.h
	g++ src/*.cpp -Iinclude -o projecto

run:
	./projecto

clean:
	rm main

clear:
	clear
