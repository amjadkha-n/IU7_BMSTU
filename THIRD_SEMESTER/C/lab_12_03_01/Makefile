CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic
UFLAGS := -lcheck -lpthread -lrt -lsubunit -lm

CFILES_DIR := ./src
CFILES := $(wildcard $(CFILES_DIR)/*.c)

INC_DIR := ./inc
INCLUDES := $(wildcard $(INC_DIR)/*.h)

OBJ_DIR := ./out
OBJECTS := $(CFILES:$(CFILES_DIR)/%.c=$(OBJ_DIR)/%.o)

STATIC_LIB_DIR := ./static_libs
STATIC_LIB_FILES := $(wildcard $(STATIC_LIB_DIR)/*.c)

STATIC_LIBS := $(STATIC_LIB_FILES:$(STATIC_LIB_DIR)/%.c=$(STATIC_LIB_DIR)/lib%.a)

SORT_LIB_DIR := ./sort_lib
SORT_LIB_FILES := $(wildcard $(SORT_LIB_DIR)/*.c)

SORT_FILES := $(SORT_LIB_FILES:$(SORT_LIB_DIR)/%.c=%)
SORT_LIBS := $(SORT_LIB_FILES:$(SORT_LIB_DIR)/%.c=$(SORT_LIB_DIR)/lib%.so)

KEY_LIB_DIR := ./key_lib
KEY_LIB_FILES := $(wildcard $(KEY_LIB_DIR)/*.c)

KEY_LIBS := $(KEY_LIB_FILES:$(KEY_LIB_DIR)/%.c=$(KEY_LIB_DIR)/lib%.so)

UNIT_DIR := ./unit_tests
UNITS := $(wildcard $(UNIT_DIR)/*.c)

UNIT_OBJECTS := $(UNITS:$(UNIT_DIR)/%.c=$(OBJ_DIR)/%.o)
UNIT_OBJECTS += $(filter-out $(OBJ_DIR)/main.o,$(OBJECTS))

APP = app.exe
UNIT_TEST = unit_tests.exe

.PHONY : unit clean run

LDFLAGS := -Wl,-rpath=$(SORT_LIB_DIR) -Wl,-rpath=$(KEY_LIB_DIR)

$(APP): $(OBJECTS) $(STATIC_LIBS) $(SORT_LIBS) $(KEY_LIBS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(STATIC_LIBS) -L  $(SORT_LIB_DIR) -l$(SORT_FILES) -ldl -o $@

UDFLAGS := -Wl,-rpath=$(SORT_LIB_DIR) -Wl,-rpath=$(KEY_LIB_DIR) -L$(SORT_LIB_DIR) -lsort -L$(KEY_LIB_DIR) -lkey

$(UNIT_TEST): $(UNIT_OBJECTS) $(SORT_LIBS) $(KEY_LIBS)
	$(CC) $(UNIT_OBJECTS) -o $@ $(UDFLAGS) $(UFLAGS)


$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(CFILES_DIR)/%.c $(INCLUDES) $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(UNIT_DIR)/%.c $(INCLUDES) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(UFLAGS) -c $< -o $@

$(STATIC_LIB_DIR)/lib%.a: $(OBJ_DIR)/%.o
	ar cr $@ $<

$(OBJ_DIR)/%.o: $(STATIC_LIB_DIR)/%.c $(INCLUDES) $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(SORT_LIB_DIR)/lib%.so: $(OBJ_DIR)/%.o
	$(CC) -o $@ -shared $<

$(OBJ_DIR)/%.o: $(SORT_LIB_DIR)/%.c $(INCLUDES) $(OBJ_DIR)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

$(KEY_LIB_DIR)/lib%.so: $(OBJ_DIR)/%.o
	$(CC) -o $@ -shared $<

$(OBJ_DIR)/%.o: $(KEY_LIB_DIR)/%.c $(INCLUDES) $(OBJ_DIR)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

run: $(APP)
	./$^

unit: $(UNIT_TEST)
	./$^

clean:
	$(RM) $(OBJ_DIR)/*.o *.exe $(STATIC_LIB_DIR)/*.a $(SORT_LIB_DIR)/*.so $(KEY_LIB_DIR)/*.so 