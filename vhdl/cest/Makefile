VHDL_FILES = starfilter.vhd clock.vhd grayscale.vhd sensor.vhd threshold.vhd counter.vhd log.vhd
ENTITY = StarFilter

ifndef STOP_TIME
	STOP_TIME = 5us
endif

ifndef THRESHOLD
	THRESHOLD = 150
endif

GHDL=ghdl-mcode
FLAGS = --stop-time=$(STOP_TIME) -gSTAR_THRESHOLD_VAL=$(THRESHOLD)

all:
	$(GHDL) -c $(VHDL_FILES) -r $(ENTITY) $(FLAGS)

wave:
	$(GHDL) -c $(VHDL_FILES) -r $(ENTITY) $(FLAGS) --vcd=sim.vcd
