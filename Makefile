PORT = /dev/ttyUSB0

FQBN = arduino:avr:nano

# must be comma separated
LIBS = ./

all:
	arduino-cli compile --fqbn $(FQBN) --library $(LIBS)

upload:
	arduino-cli upload --fqbn $(FQBN) --port $(PORT)
