all : greedy sa sog_test

greedy : greedy.cpp SumofGaussians.cpp SumofGaussians.h
	g++ -std=c++11 greedy.cpp SumofGaussians.cpp SumofGaussians.h -o greedy

sa : sa.cpp SumofGaussians.cpp SumofGaussians.h
	g++ -std=c++11 sa.cpp SumofGaussians.cpp SumofGaussians.h -o sa
	
sog_test : sog_test.cpp SumofGaussians.cpp SumofGaussians.h
	g++ sog_test.cpp SumofGaussians.cpp SumofGaussians.h -o sog_test

clean:
	rm -f greedy sa sog_test
	rm -f *.o