OBJS = main.o sort.o
result: $(OBJS)
	@echo $^
	@echo $@ #加了@的话命令不会被显示出来#
	gcc $^ -o $@

$(OBJS): sort.h
clean:
	rm $(OBJS)
	rm result