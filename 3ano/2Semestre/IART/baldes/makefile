JFLAGS = -g
JC = javac
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
    Buckets.java \
    Operation.java \
    node/Node.java \

default: classes

classes: $(CLASSES:.java=.class)

clean:
	$(RM) $(CLASSES:.java=.class)