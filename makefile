br:
	g++ -o program.exe src/*.cpp     && program.exe
br1:
	g++ -o program.exe src/*.cpp -O1 && program.exe
br2:
	g++ -o program.exe src/*.cpp -O2 && program.exe
br3:
	g++ -o program.exe src/*.cpp -O3 && program.exe
