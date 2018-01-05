all:
	g++ -o xboy *.cpp cpu/*.cpp cpu/instructions/*.cpp memory/*.cpp -Wall -std=c++1z
