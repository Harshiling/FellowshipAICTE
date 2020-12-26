todo.o:
	g++ -c -std=c++11 -Wall todo.cpp -o to

app: todo.o
	g++ to -o todo.out

test: app
	npm run test

clean:
	rm -f todo.o todo.out

install:
	npm install
