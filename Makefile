all:
	g++ -o xboy *.cpp cpu/*.cpp cpu/operations/*.cpp -Wall -std=c++1z
