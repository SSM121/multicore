All: Server Phase1 Phase2
Server: server.o
	g++ -lrt -std=c++11 -o Server server.cpp
Phase1: phase1.o
	g++ -lrt -std=c++11 -o Phase1 phase1.cpp
Phase2: phase2.o
	g++ -lrt -std=c++11 -o Phase2 phase2.cpp
server.o: server.cpp
	g++ -lrt -std=c++11 -c -o server.o server.cpp
phase1.o: phase1.cpp
	g++ -lrt -std=c++11 -c -o phase1.o phase1.cpp
phase2.o: phase2.cpp
	g++ -lrt -std=c++11 -c -o phase2.o phase2.cpp
clean:
	rm *.o
	rm Server
	rm Phase1
	rm Phase2

