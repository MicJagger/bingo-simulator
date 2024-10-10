br:
	g++ -o program src/*.cpp     && ./program
br1:
	g++ -o program src/*.cpp -O1 && ./program
br2:
	g++ -o program src/*.cpp -O2 && ./program
br3:
	g++ -o program src/*.cpp -O3 && ./program
brw:
	g++ -o program src/*.cpp     && program.exe
br1w:
	g++ -o program src/*.cpp -O1 && program.exe
br2w:
	g++ -o program src/*.cpp -O2 && program.exe
br3w:
	g++ -o program src/*.cpp -O3 && program.exe
