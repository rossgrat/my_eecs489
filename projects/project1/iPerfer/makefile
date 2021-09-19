OBJS=server.o client.o main.o
EXEC=iPerfer
all: $(EXEC)

iPerfer:	$(OBJS)
			$(CC) -o $(EXEC) $(OBJS)
clean: 
		-rm $(OBJS) $(EXEC)