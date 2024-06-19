# Compiler options
JAVAC = javac
JFLAGS = -cp Dependencys/json-20230227.jar

# Source directory
SRCDIR = src

# Output directory
OUTDIR = out

# Java source files
SOURCES = $(shell find src -name "*.java")

# Main class
MAIN = FeedReaderMain #-ne

# Default target
default: run

# Target to compile the Java source files
build:
	$(JAVAC) $(JFLAGS) -d $(OUTDIR) $(SOURCES)

# Target to run the application
run: build
	java $(JFLAGS):$(OUTDIR) $(MAIN)

# Target to clean the project
clean:
	rm -rf $(OUTDIR)

.PHONY: default build clean

# make run 