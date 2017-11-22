
#This target compiles all the files.
treesearch: ADSMainFile.o ADSFunc1.o ADSFunc2.o
	g++ ADSMainFile.o ADSFunc1.o ADSFunc2.o -o treesearch

#This target compiles the file containing code block to take input from input.txt file.	
ADSMainFile.o: ADSMainFile.cpp
	g++ -c ADSMainFile.cpp

#This target compiles the file containing the splitNode and insertElem functions.	
ADSFunc1.o: ADSFunc1.cpp
	g++ -c ADSFunc1.cpp
	
#This target compiles the file containing the searchInt and rangeSearch and printManip functions.	
ADSFunc2.o: ADSFunc2.cpp
	g++ -c ADSFunc2.cpp

clean:
	rm -rf *.o treesearch