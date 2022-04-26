TARGET = src/ICP_Project
OUTPUT = qMakefile

all: $(TARGET)
	make -f qMakefile

run: all
	./umleditor

$(TARGET): $(TARGET).pro
	qmake -o $(OUTPUT) $(TARGET).pro

clean:
	rm -f UmlEditor *.o ui_UmlEditor.h moc_UmlEditor.cpp qMakefile