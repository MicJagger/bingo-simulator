br:
	g++ -o program src/*.cpp     && program
br1:
	g++ -o program src/*.cpp -O1 && program
br2:
	g++ -o program src/*.cpp -O2 && program
br3:
	g++ -o program src/*.cpp -O3 && program
