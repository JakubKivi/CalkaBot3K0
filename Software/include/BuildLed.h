#ifndef BUILDLED_H
#define BUILDLED_H

#include <avr/io.h>

class BuildLed {
private:
    volatile uint8_t *port;  // Port, do którego podłączona jest dioda
    uint8_t pin;              // Numer pinu
    uint8_t *ddr;              // Numer rejestru I/O
    uint8_t error_count;      // Liczba błędów do migania
    static BuildLed* active_led;  // Statyczny wskaźnik na aktualny obiekt
    

public:
    // Konstruktor
    BuildLed(volatile uint8_t *port, uint8_t pin);

    // Metoda inicjalizująca
    void init();

    // Metoda do migania w pętli (KillError)
    void killError(uint8_t n);

    // Metoda do migania w tle (ShowError)
    void showError(uint8_t n);

    // Metoda dostępu do zmiennej error_count
    uint8_t getErrorCount() const;

    // Statyczna metoda ustalająca aktywny obiekt
    static void setActiveLed(BuildLed* led);
    static BuildLed* getActiveLed();

    // Statyczna zmienna przechowująca wskaźnik na aktywny obiekt
    static volatile uint8_t* getActivePort();
    static uint8_t getActivePin();
};

#endif
