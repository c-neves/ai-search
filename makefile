.DEFAULT_GOAL := build
.PHONY: build clean exec
.PRECIOUS: .bin/%.o .bin/graph/%.o

##
# `make build`
#
# Lists with the 5 search algorithms.
_SEARCH_ALGORITHMS := depth_first_search breadth_first_search \
	best_first_search a_star hill_climbing

build: $(addprefix .bin/, $(_SEARCH_ALGORITHMS))

.bin/%: .bin/%.o .bin/maze.o .bin/graph.o .bin/graph/node.o .bin/graph/path.o | .bin
	g++ -Wall $(<) .bin/maze.o .bin/graph.o .bin/graph/node.o .bin/graph/path.o -o $(@)

.bin/%.o: %/main.cpp | .bin
	g++ -c -Wall $(<) -o $(@)

.bin/maze.o: maze/maze.cpp maze/maze.hpp | .bin
	g++ -c -Wall $(<) -o $(@)

.bin/graph.o: graph/graph.cpp graph/graph.hpp | .bin
	g++ -c -Wall $(<) -o $(@)

.bin/graph/%.o: graph/%.cpp graph/graph.hpp | .bin/graph
	g++ -c -Wall $(<) -o $(@)

.bin/graph: | .bin
	mkdir -p .bin/graph

.bin:
	mkdir -p .bin

##
# `make clean`
#
clean:
	rm -rf .bin

##
# `make exec a=bfs n=3`
#
# Which algorithm to execute.
ifndef a
_ALGORITHM := depth_first_search
else ifeq '$(a)' 'dfs'
_ALGORITHM := depth_first_search
else ifeq '$(a)' 'bfs'
_ALGORITHM := breadth_first_search
else ifeq '$(a)' 'bsfs'
_ALGORITHM := best_first_search
else ifeq '$(a)' 'as'
_ALGORITHM := a_star
else ifeq '$(a)' 'hc'
_ALGORITHM := hill_climbing
else
_ALGORITHM := $(a)
endif

# How many executions.
ifndef n
_N := 1
else
_N := $(n)
endif

# if n > 1
ifneq '$(_N)' '1'
# stdin
ifdef i
_STDIN := $(i)
else
_STDIN := /dev/null
endif
# stdout
ifdef o
_STDOUT := $(o)
else
_STDOUT := /dev/null
endif
# stderr
ifdef e
_STDERR := $(e)
else
_STDERR := /dev/null
endif
endif

exec: .bin/$(_ALGORITHM)
	exec .bin/$(_ALGORITHM)

# For debugging.
_TIMESTAMP := $(shell date '+%Y-%m-%d_%H:%M:%S.%N')
_MAZE := $(m)
_execlog: .bin/$(_ALGORITHM)
	@mkdir -p .execlog
	@mkdir .execlog/$(_TIMESTAMP)
	@cp .bin/$(_ALGORITHM) .execlog/$(_TIMESTAMP)/$(_ALGORITHM).binary
	@cp __mazes__/$(_MAZE).txt .execlog/$(_TIMESTAMP)/stdin
	cd .execlog/$(_TIMESTAMP) && \
		./$(_ALGORITHM).binary \
			< stdin \
			> stdout \
			2> stderr; \
		echo $$? > exit_status
	@cat .execlog/$(_TIMESTAMP)/stdout
ifdef _d
	@echo vvv---+---+---stderr---+---+---vvv
	@cat .execlog/$(_TIMESTAMP)/stderr
endif

# TODO: time N EXECUTIONS + average time for each alg for each maze
# ifeq '$(_N)' '1'
# 	exec .bin/$(_ALGORITHM)
# else
# 	for i in $$(seq $(_N)); do ./.bin/$(_ALGORITHM) < $(_STDIN) > $(_STDOUT) 2> $(_STDERR); done
# endif
# 	echo "foo"
