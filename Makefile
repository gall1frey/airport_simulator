all: beautify.o ip_op.o decisions.o airport

ip_op.o: ip_op.c
	gcc -c ip_op.c
beautify.o: beautify.c
	gcc -c beautify.c
decisions.o: decisions.c
	gcc -c decisions.c
airport: ip_op.h ip_op.o decisions.h decisions.o beautify.h beautify.o main.c 
	gcc -o airport ip_op.o decisions.o beautify.o main.c
clean:
	rm *.o