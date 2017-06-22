OBJ =  main.o appdevwave.o screen.o
APPNAME = main.a

$(APPNAME) : $(OBJ)
	gcc -o $(APPNAME) $(OBJ) -lm -lcurl

%.o : %.c
	gcc -c -o $@ $<

clean:
	rm $(APPNAME) $(OBJ)
due:
	tar -cvf appdev.tar *.c *.h makefile
