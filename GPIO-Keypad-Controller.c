#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_G_PIN 11 //PINO DO LED VERDE
#define LED_B_PIN 12 //PINO DO LED AZUL
#define LED_R_PIN 13 //PINO DO LED VERMELHO

// Matrizes com nomes de colunas e linhas
const uint LINHAS[4] = {1, 2, 3, 4};
const uint COLUNAS[4] = {5, 6, 7, 8};


// Mapeamento das teclas em uma matriz 4x4
char teclas[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Inicializando os pinos de GPIO para o teclado
void iniciar_teclado() {

    // Definição das linhas como saídas e inicialização em nível baixo
    for (int i = 0; i < 4; i++) {
        gpio_init(LINHAS[i]);
        gpio_set_dir(LINHAS[i], GPIO_OUT);
        gpio_put(LINHAS[i], 0);
    }

    // Definição das colunas como entradas com resistores de pull-down
    for (int i = 0; i < 4; i++) {
        gpio_init(COLUNAS[i]);
        gpio_set_dir(COLUNAS[i], GPIO_IN);
        gpio_pull_down(COLUNAS[i]);
    }
}

// Varredura do teclado e retorno da tecla pressionada
char leitura_teclado() {
    for (int row = 0; row < 4; row++) {
        // Coloca a linha atual em nível alto
        gpio_put(LINHAS[row], 1);

        for (int col = 0; col < 4; col++) {
            // Verifica se a tecla foi pressionada
            if (gpio_get(COLUNAS[col])) {
                // Espera um tempo para estabilização da tecla pressionada
                sleep_ms(50);

                gpio_put(LINHAS[row], 0); // Reseta a linha atual

                return teclas[row][col];
            }
        }

        // Coloca a linha atual novamente para nível baixo
        gpio_put(LINHAS[row], 0);
    }

    return 0; // Nenhuma tecla pressionada
}

int main() {
    stdio_init_all();
    
    // Inicializa o teclado
    iniciar_teclado();
// Inicializa os LEDs
    gpio_init(LED_R_PIN);
    gpio_set_dir(LED_R_PIN, GPIO_OUT);
    gpio_init(LED_G_PIN);  // inicia o verde
    gpio_set_dir(LED_G_PIN, GPIO_OUT);
    gpio_init(XXXXXXX);  // inicia o azul
    gpio_set_dir(XXXXXXX, XXXXXXX);

    while (true) {
        char tecla = leitura_teclado();
        printf("Tecla pressionada: %c\n", tecla);
        


        
        // Configuração dos LEDs com base na tecla pressionada
        switch (tecla) {
            case 'A':
                set_leds(1, 0, 0); // Botão A acende o LED vermelho
                break;
            case 'B':
                set_leds(x, x, x); // Botão B acende o LED azul
                break;
            case 'C':
                set_leds(0, 1, 0); // Botão C acende o LED verde
                break;
            case 'D':
                set_leds(1, 1, 1); // Botão D acende todos os LEDs
                break;
            default:
                set_leds(0, 0, 0); // Desliga todos os LEDs
                break;
    } 
    
    sleep_ms(100); // Estabilização

    }

    return 0;
}


