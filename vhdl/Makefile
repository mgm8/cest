VHDL_FILES = starfilter.vhd clock.vhd grayscale.vhd sensor.vhd threshold.vhd counter.vhd log.vhd
ENTITY = StarFilter

ifndef STOP_TIME
	STOP_TIME = 5us
endif

ifndef THRESHOLD
	THRESHOLD = 150
endif

FLAGS = --stop-time=$(STOP_TIME) -gSTAR_THRESHOLD_VAL=$(THRESHOLD)

all:
	ghdl-mcode -c $(VHDL_FILES) -r $(ENTITY) $(FLAGS)

wave:
	ghdl-mcode -c $(VHDL_FILES) -r $(ENTITY) $(FLAGS) --vcd=sim.vcd
