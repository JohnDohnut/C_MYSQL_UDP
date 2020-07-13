include makefile.conf

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

clean:
	$(RM) $(OBJS)
	$(RM) $(TARGET)

remake:
	$(RM) $(OBJS)
	$(RM) $(TARGET)
	make

