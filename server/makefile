include makefile.conf

all : $(TARGET)

$(TARGET) : $(OBJS_CURR) $(OBJS_UPPER)
	$(CC) -o $(TARGET) $(OBJS_CURR) $(OBJS_UPPER) $(MYSQL)

$(OBJS_UPPER) : $(SRCS_UPPER)
	$(CC) -c $(SRCS_UPPER) $(MYSQL)
$(OBJS_CURR) : $(SRCS_CURR)
	$(CC) -c $(SRCS_CURR) $(MYSQL)

clean:
	$(RM) *.o
	$(RM) $(TARGET)

remake:
	$(RM) $(OBJS)
	$(RM) $(TARGET)
	make

