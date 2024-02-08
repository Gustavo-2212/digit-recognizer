CMD = gcc 
RM  = rm -rf

BUILD_DIR = build

SCRS = train.c test.c

OBJS = $(patsubst %, $(BUILD_DIR)/%.exe, $(basename $(SCRS)))
$(shell mkdir -p $(dir $(OBJS)) > /dev/null)


.PHONY: all
all: $(OBJS)

$(BUILD_DIR)/%.exe: src/%.c
	$(CMD) -o $@ $<

.PHONY: clean
clean:
	$(RM) $(BUILD_DIR)