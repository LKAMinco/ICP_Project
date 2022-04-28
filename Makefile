TARGET = src/ICP_Project
OUTPUT = qMakefile

all: compile
	make -f qMakefile

run: all
	./umleditor

compile: $(TARGET).pro
	qmake -d -Wall -o $(OUTPUT) $(TARGET).pro

clean:
	rm -f UmlEditor *.o ui_UmlEditor.h moc_UmlEditor.cpp qMakefile .qmake.stash moc_predefs.h