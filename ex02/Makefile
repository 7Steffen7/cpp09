
NAME = PmergeMe

CXX = c++

# -Wpedantic warning if code is not strictly c++98
# -MMD create dependency files
# -MP add phony target for each dependency // prevent error if renaming or deleting header files
# -02 optimization flag
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -MMD -MP -O2 -g

SRC = main.cpp \
		PmergeMe.cpp \


SRC_DIR:=.

OBJ_DIR:=obj

# subst = replace / with @ in all object files
# addprefix add prefix obj/ to all .o files
OBJ:=$(addprefix $(OBJ_DIR)/,$(subst /,@,$(SRC:.cpp=.o)))

DEPENDS:=$(OBJ:.o=.d)

# @$(MAKE) ensures the right version of make is called
# -j multicore optimisation
all:
	@$(MAKE) $(NAME) -j


# $^ all prerequisites of target
# -o $@ output to target name
$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $^ -o $@

# - makes it optinal so if dependency file does not exist no error will occur
-include $(DEPENDS)

.SECONDEXPANSION:
$(OBJ_DIR)/%.o: $(SRC_DIR)/$$(subst @,/,$$*).cpp
	@$(CC) $(CXXFLAGS) $(addprefix -iquote ,$(INCLUDE_DIR)) -c $< -o $@

$(OBJ): $(OBJ_DIR)

# -p create parent directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
