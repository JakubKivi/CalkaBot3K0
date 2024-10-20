# Zmienne
MCU = atmega328p               # Typ mikrokontrolera
CC = avr-gcc                   # Kompilator
OBJCOPY = avr-objcopy           # Narzędzie do konwersji
AVRDUDE = avrdude               # Narzędzie do programowania
PORT = COM3                     # Port, do którego podłączony jest mikrokontroler
BAUD = 115200                   # Prędkość transmisji
CFLAGS = -mmcu=$(MCU) -Os -DF_CPU=16000000L  # Flagi kompilacji, zdefiniowanie F_CPU na 16 kHz
SRC_FILES = main.c 		       # Pliki źródłowe
ELF_FILE = main.elf            # Plik ELF
HEX_FILE = main.hex            # Plik HEX

# Cel główny
all: $(HEX_FILE)

# Kompilacja do pliku ELF
$(ELF_FILE): $(SRC_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Konwersja do pliku HEX
$(HEX_FILE): $(ELF_FILE)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# Flashowanie mikrokontrolera
flash: $(HEX_FILE)
	$(AVRDUDE) -c arduino -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$<:i

# Cel do czyszczenia
clean:
	rm -f $(ELF_FILE) $(HEX_FILE)