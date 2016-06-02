# Global parameters
GCC = g++.exe
FLAGS =	-Wall -fmessage-length=0 -I..\includes -O2 -DDEBUG
TARGET = bin\MultiFileRename.exe

all: $(TARGET)

# Create target application
$(TARGET): obj\main.o obj\maindialog.o res\resource.res
	$(GCC) -mwindows -o $@ $^

#Resource
res\resource.res: res\resource.rc
	windres.exe --input-format=rc -O coff -o $@ -i $<

#Root
obj\main.o: src\main.cpp
	$(GCC) $(FLAGS) -o $@ -c $<

#Dialogs
obj\maindialog.o: src\dialogs\maindialog.cpp src\dialogs\maindialog.h
	$(GCC) $(FLAGS) -o $@ -c $<

# Clean targets
clean:
	del obj\*.o
	del res\*.res
	del $(TARGET)