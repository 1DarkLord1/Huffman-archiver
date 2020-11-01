CXX = g++
CXXFLAGS = -O2 -Wall -Werror -Wextra -std=c++11 -Iinclude

MAIN = huff
TEST = huff_test
SRCDIR = src
TESTDIR = test
MAINOBJ = obj/main.o
OBJDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))
TEST_OBJECTS = $(patsubst $(TESTDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(TESTDIR)/*.cpp))

all: $(MAIN)

$(MAIN): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(MAIN)

$(TEST): $(TEST_OBJECTS) $(OBJECTS)
	$(CXX) $(TEST_OBJECTS) $(filter-out $(MAINOBJ), $(OBJECTS)) -o $(TEST)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(OBJDIR)/*.d)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(MAIN) $(TEST)

.PHONY: clean all
