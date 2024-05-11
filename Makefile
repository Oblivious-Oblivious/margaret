all: run_example

run_example:
	em build app debug
	./export/margaret examples/test.marg
