CMD = gcc 
RM  = rm -rf

BUILD_DIR = build
TEMP_DIR  = src/temp

SCRS = train.c test.c train_2.c test_2.c

OBJS = $(patsubst %, $(BUILD_DIR)/%.exe, $(basename $(SCRS)))
$(shell mkdir -p $(dir $(OBJS)) > /dev/null)
$(shell mkdir -p $(TEMP_DIR) > /dev/null)


.PHONY: all
all: $(OBJS)

$(BUILD_DIR)/%.exe: src/%.c
	$(CMD) -o $@ $<

.PHONY: clean
clean:
	$(RM) $(BUILD_DIR) $(TEMP_DIR)