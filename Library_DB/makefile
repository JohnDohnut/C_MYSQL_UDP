include makefile.conf

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(MYSQL)

$(OBJS) : $(SRCS)
	$(CC) -c $(SRCS) $(MYSQL)

clean:
	$(RM) $(OBJS)
	$(RM) $(TARGET)

remake:
	$(RM) $(OBJS)
	$(RM) $(TARGET)
	make
flag:
	@echo $(MYSQL)


