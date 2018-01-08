all:
	g++ -o xboy *.cpp debug/*.cpp cpu/*.cpp cpu/instructions/*.cpp memory/*.cpp -Wall -std=c++1z
