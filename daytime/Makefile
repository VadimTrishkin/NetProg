CXX = g++
CXXFLAGS = -Wall

all: daytime_client

daytime_client: daytime_client.o
	$(CXX) $(CXXFLAGS) -o daytime_client daytime_client.o

daytime_client.o: daytime_client.cpp
	$(CXX) $(CXXFLAGS) -c daytime_client.cpp

clean:
	rm -f *.o daytime_client
