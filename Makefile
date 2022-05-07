TARGET = src/ICP_Project
OUTPUT = qMakefile

all: compile
	make -f qMakefile

run: all
	./umleditor

compile: $(TARGET).pro
	qmake -d -Wall -o $(OUTPUT) $(TARGET).pro

doxygen:
	doxygen doc/Doxyfile

clean:
	rm -f UmlEditor *.o ui_UmlEditor.h moc_UmlEditor.cpp qMakefile .qmake.stash moc_predefs.h ui_seqentity.h ui_classentity.h moc_seqscene.cpp moc_seqentity.cpp moc_scene.cpp moc_classentity.cpp -r html -r latex

pack:
	zip -r xhrabo15-xsmyka01.zip src examples Makefile README.txt README.md doc/Doxyfile