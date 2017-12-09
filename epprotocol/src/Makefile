OBJECTS = epp

obj = DLT645/app645.o \
	DLT645/main645.o \
	debug.o \
	safe.o \
	PubFunctions.o \
	pstring.o \
	main.o
	
PKG_NAME=docs
	
all : $(OBJECTS)

epp: $(obj)
	$(CC) $(LDFLAGS) $^ -o $@ -g
	
app645.o:DLT645/app645.c
	$(CC) $(CFLAGS)  -c $< -g
	
main645.o:DLT645/main645.c
	$(CC) $(CFLAGS)  -c $< -g

debug.o:debug.c
	$(CC) $(CFLAGS)  -c $< -g
safe.o:safe.c
	$(CC) $(CFLAGS)  -c $< -g
PubFunctions.o:PubFunctions.c
	$(CC) $(CFLAGS)  -c $< -g
pstring.o:pstring.c
	$(CC) $(CFLAGS)  -c $< -g
	
main.o:main.c
	$(CC) $(CFLAGS)  -c $< -g
	
	

.PHONY:clean

clean:
	@-rm *.o  epp
