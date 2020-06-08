OBJS = main.o sort.o
result: $(OBJS)
	gcc $(OBJS) -o result
	rm $(OBJS)

main.o: main.c sort.h
	gcc -pthread -c main.c

sort.o: sort.c sort.h
	gcc -pthread -c sort.c

clean:
	rm $(OBJS)
	rm result