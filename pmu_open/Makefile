all: perf_event_open test perf_event_open_1
test: test.c
	@echo "compiling test..."
	@$(CC) test.c -o test

perf_event_open: perf_event_open.c
	@echo "compiling perf_event_open..."
	@$(CC) perf_event_open.c -o perf_event_open 

perf_event_open_1: perf_event_open_1.c
	@echo "compiling perf_event_open_1..."
	@$(CC) perf_event_open_1.c -o perf_event_open_1

runtests: all
#	@echo "load module"
#	@./load-module
#	@echo "run"
#	@./test
#	@echo "unload module"
#	@./unload-module
	@./perf_event_open 64
#	@./perf_event_open_1 64

clean:
	rm -f test perf_event_open_1 perf_event_open *.o *~ 

