all: WordCount.o WC_Mapper.o WC_Reducer.o mapreduce
	g++ -o WC_Mapper WC_Mapper.o WordCount.o
	g++ -o WC_Reducer WC_Reducer.o WordCount.o

WC_Mapper.o: WC_Mapper.cpp
	g++ -c WC_Mapper.cpp
	
WC_Reducer.o: WC_Reducer.cpp
	g++ -c WC_Reducer.cpp

WordCount.o: WordCount.cpp
	g++ -c WordCount.cpp
mapreduce:
	gcc mapreduce.c -o mapreduce

clean:
	rm -f *.o && rm mapreduce
berk:
	./mapreduce 5 WC_Mapper < ../input/input.txt
