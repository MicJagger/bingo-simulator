build-run:
	g++ -o bingo-simulator.exe src/*.cpp && bingo-simulator.exe
build-run-o1:
	g++ -o bingo-simulator.exe src/*.cpp -O1 && bingo-simulator.exe
build-run-o2:
	g++ -o bingo-simulator.exe src/*.cpp -O2 && bingo-simulator.exe
build-run-o3:
	g++ -o bingo-simulator.exe src/*.cpp -O3 && bingo-simulator.exe
