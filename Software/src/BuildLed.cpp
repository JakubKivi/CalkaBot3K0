#include "../include/BuildLed.h"
#include <avr/interrupt.h>
#include <util/delay.h>

// Inicjalizacja wskaźnika na aktywny obiekt (na początku NULL)
BuildLed* BuildLed::active_led = 0;

// Konstruktor klasy BuildLed
BuildLed::BuildLed(volatile uint8_t *port, uint8_t pin) {
    this->port = port;
    this->pin = pin;
    this->error_count = 0;
    this->init();
    active_led=this;
}

// Inicjalizacja - ustawienie pinu jako wyjście i diody w stanie niskim
void BuildLed::init() {
    *(ddr) |= (1 << pin);  // DDRx - ustawienie pinu jako wyjście
    *(port) &= ~(1 << pin);  // Ustawienie diody w stan niski
}

// Metoda KillError - nieskończona pętla migania
void BuildLed::killError(uint8_t n) {
    while (1) {
        for (uint8_t i = 0; i < n; i++) {
            *(port) |= (1 << pin);  // Włącz LED
            _delay_ms(200);
            *(port) &= ~(1 << pin);  // Wyłącz LED
            _delay_ms(200);
        }
        _delay_ms(2000);
    }
}

// Metoda ShowError - miganie w tle przy pomocy przerwań
void BuildLed::showError(uint8_t n) {
    this->error_count = n;

    // Konfiguracja timera do generowania przerwań co 200ms (prescaler 256)
    TCCR1B |= (1 << WGM12) | (1 << CS12);  // Tryb CTC, prescaler 256
    OCR1A = 17500;                          // Czas trwania przerwania (zakładając 16MHz zegar)
    TIMSK1 |= (1 << OCIE1A);               // Włączenie przerwań dla Compare Match
    sei();                                 // Włączenie przerwań globalnych
}

// Metoda dostępu do zmiennej error_count
uint8_t BuildLed::getErrorCount() const {
    return this->error_count;
}

// Statyczna metoda ustalająca aktywny obiekt
void BuildLed::setActiveLed(BuildLed* led) {
    active_led = led;
}

// Statyczna metoda zwracająca aktywny obiekt
BuildLed* BuildLed::getActiveLed() {
    return active_led;
}

// Zwrócenie portu aktywnego obiektu
volatile uint8_t* BuildLed::getActivePort() {
    if (active_led != 0) {
        return active_led->port;
    }
    return 0;  // Jeśli aktywny obiekt jest null
}

// Zwrócenie pinu aktywnego obiektu
uint8_t BuildLed::getActivePin() {
    if (active_led != 0) {
        return active_led->pin;
    }
    return 0xFF;  // Jeśli aktywny obiekt jest null
}

// Przerwanie Timer1 Compare Match - obsługuje miganie w ShowError
ISR(TIMER1_COMPA_vect) {
    static uint8_t blink_counter = 0;
    static uint16_t wait_counter = 0;

    // Dostęp do aktywnej instancji BuildLed
    BuildLed* led = BuildLed::getActiveLed();  // Pobranie wskaźnika na aktywny obiekt

    if (led != 0 ) {
        if (blink_counter < 2 * led->getErrorCount() && wait_counter==0 ) {
            if (blink_counter % 2 == 0) {
                *(led->getActivePort()) |= (1 << led->getActivePin());  // Włącz LED
            } else {
                *(led->getActivePort()) &= ~(1 << led->getActivePin());  // Wyłącz LED
            }
            blink_counter++;
        } else {
            blink_counter = 0;
            wait_counter++;
            if (wait_counter >= 10) {  // 200ms * 10 (2 sekundy)
                *(led->getActivePort()) &= ~(1 << led->getActivePin());  // Wyłącz LED
                wait_counter =0;
            }
        }
    } 
}
