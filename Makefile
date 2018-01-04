all:
	g++ -o xboy *.cpp cpu/*.cpp cpu/operations/*.cpp memory/*.cpp -Wall -std=c++1z
