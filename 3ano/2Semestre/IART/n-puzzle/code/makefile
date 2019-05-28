CXX		 = g++
CXXFLAGS = -std=c++11 -Ofast
LDFLAGS  =
DEPS	 = main.cpp node.cpp node.h algorithms.cpp algorithms.h interface.cpp interface.h mapLoader.cpp mapLoader.h ui_utilities.cpp ui_utilities.h makefile
OBJFILES = main.o node.o algorithms.o interface.o mapLoader.o ui_utilities.o
TARGET	 = main


all: $(TARGET)


$(TARGET): $(OBJFILES) $(DEPS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)


clean:
	rm -f $(OBJFILES) $(TARGET) *~

recompile: makefile
	make clean
	make $(TARGET)