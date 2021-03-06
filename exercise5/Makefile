SOURCES=MsgQueue.cpp main.cpp
OBJECTS=$(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.o))
DEPS=$(SOURCES:.cpp=.d)
EXE=$(addprefix $(BIN_DIR)/,prog)
CXXFLAGS=-I.
ARCH ?= host
LIB=-lpthread

# Making for host
# > type:  make ARCH=host
ifeq (${ARCH},host)
CXX=g++
BUILD_DIR=build/host
BIN_DIR=bin/host
endif

# Making for target
#  > type:  make ARCH=target
ifeq (${ARCH},target)
CXX=arm-rpizw-g++
BUILD_DIR=build/target
BIN_DIR=bin/target
endif

$(EXE): $(BIN_DIR) $(DEPS) $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) $(LIB)

$(BUILD_DIR)/%.o: %.cpp $(BUILD_DIR)
	${CXX} -c -o $@ $<

$(BUILD_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

# Rule that describes how a .d (dependency) file is created from a .cpp
# file
# Similar to the assigment that you just completed %.cpp -> %.o
%.d: %.cpp
	$(CXX) -MT$@ -MM $(CXXFLAGS) $< > $@
	$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $< >> $@

clean:
	@rm -rf bin/
	@rm -rf build/
	rm *.d
	rm *.format
	rm *.tidy


format: $(SOURCES:.cpp=.format)
%.format: %.cpp
	@echo "Formatting file '$<'"
	@clang-format -i $<
	@echo "" > $@

tidy: $(SOURCES:.cpp=.tidy)
%.tidy: %.cpp
	@echo "Tidying file '$<'"
	@clang-tidy $< -- $(CXXFLAGS)
	@echo "" > $@

ifneq ($(filter-out clean format tidy,$(MAKECMDGOALS)),)
-include $(DEPS)
endif
