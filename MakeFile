.PHONY: all clean
OBJS_LIB = graph.o
OBJS_APP = main.o tests.o
MYLIBNAME = libgraph.a
MYAPPNAME = app.out

all: $(MYLIBNAME) $(MYAPPNAME)
clean:
	$(RM) -f $(OBJS_LIB)
	$(RM) -f $(OBJS_APP)
	$(RM) -f $(OBJS_LIB:.o=.d)
	$(RM) -f $(OBJS_APP:.o=.d)
	$(RM) -f $(MYLIBNAME)
	$(RM) -f $(MYAPPNAME)

# Параметры компиляции, указанные в задании
CFLAGS= -std=c11 -pedantic -Wall -O1
INCLUDES+= -I ./include
vpath %.h include src
vpath %.c src

$(MYLIBNAME): $(OBJS_LIB)
	$(AR) -rsc $@ $^
%.o: %.c
	gcc -MD $(CFLAGS) $(INCLUDES) -c -o $@ $<
-include $(OBJS_LIB:.o=.d)
$(MYAPPNAME): $(OBJS_APP) $(MYLIBNAME)
	gcc -o $@  $^
-include $(OBJS_APP:.o=.d)