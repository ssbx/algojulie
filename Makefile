.PHONY: run
run: monapp
	./monapp -x 4 -y 4 -z 8 -f ./test.csv
monapp: main.c
	cc -o monapp main.c
