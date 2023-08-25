#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>


/*
    ALUNOS:
        Nicolas Petruci Penga (2211600184)
        Lucas Roberto (2211600445)
        Felipe Delgado (2211600317)
*/
using namespace std;

const int numeroDeRetangulos = 10;
const int larguraDaTela = 900;
const int alturaDaTela = 700;
const float velocidadeDoPersonagem = 7.5;

struct AreaDoRetangulo {
    float x, y, xDaLargura, yDaAltura;
    ALLEGRO_BITMAP* imagem;
    bool visibilidade;
};

bool key[8] = { false, false, false, false, false, false, false, false };

void desenhandoRetangulo(AreaDoRetangulo r) {
    if (r.visibilidade) {
        al_draw_rectangle(r.x, r.y, r.x + r.xDaLargura, r.y + r.yDaAltura, al_map_rgb(255, 255, 255), 0);
        al_draw_bitmap_region(r.imagem, 0, 0, al_get_bitmap_width(r.imagem), al_get_bitmap_height(r.imagem), r.x, r.y, 0);
    }
}

bool hitBox(AreaDoRetangulo r1, AreaDoRetangulo r2) {
    if (r1.x + r1.xDaLargura > r2.x &&
        r2.x + r2.xDaLargura > r1.x &&
        r1.y + r1.yDaAltura > r2.y &&
        r2.y + r2.yDaAltura > r1.y) {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    ALLEGRO_DISPLAY* tela = NULL;
    ALLEGRO_EVENT_QUEUE* filaDeAcoes = NULL;
    ALLEGRO_EVENT acoes;
    ALLEGRO_BITMAP* imagemDeFundo = NULL;
    ALLEGRO_BITMAP* imagem[numeroDeRetangulos];
    ALLEGRO_TIMER* temporizador = NULL;

    float x = larguraDaTela;
    float y = alturaDaTela;

    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();

    filaDeAcoes = al_create_event_queue();
    temporizador = al_create_timer(0.1);

    al_register_event_source(filaDeAcoes, al_get_mouse_event_source());
    al_register_event_source(filaDeAcoes, al_get_keyboard_event_source());
    al_register_event_source(filaDeAcoes, al_get_timer_event_source(temporizador));

    tela = al_create_display(x, y);
    imagemDeFundo = al_load_bitmap("corrupcaoDoMapa.png");

    AreaDoRetangulo r[numeroDeRetangulos];

    for (int i = 0; i < numeroDeRetangulos; i++) {
        char nome_arq[50];
        if (i == 0) {
            sprintf(nome_arq, "laminaSolitaria.png");
            imagem[i] = al_load_bitmap(nome_arq);
        }
        else {
            sprintf(nome_arq, "Goblin%d.png", i);
            imagem[i] = al_load_bitmap(nome_arq);
        }
    }

    for (int i = 0; i < numeroDeRetangulos; i++) {
        if (i == 0) {
            r[i].x = 450;
            r[i].y = 450;
            r[i].xDaLargura = 25;
            r[i].yDaAltura = 25;
            r[i].imagem = imagem[i];
            r[i].visibilidade = true;
        }
        if (i == 1) {
            r[i].x = 200;
            r[i].y = 100;
            r[i].xDaLargura = 30;
            r[i].yDaAltura = 30;
            r[i].imagem = imagem[i];
            r[i].visibilidade = true;
        }
        if (i == 2) {
            r[i].x = 400;
            r[i].y = 300;
            r[i].xDaLargura = 30;
            r[i].yDaAltura = 30;
            r[i].imagem = imagem[i];
            r[i].visibilidade = true;
        }
        if (i == 3) {
            r[i].x = 300;
            r[i].y = 150;
            r[i].xDaLargura = 30;
            r[i].yDaAltura = 30;
            r[i].imagem = imagem[i];
            r[i].visibilidade = true;
        }
        if (i == 4) {
            r[i].x = 40;
            r[i].y = 125;
            r[i].xDaLargura = 30;
            r[i].yDaAltura = 30;
            r[i].imagem = imagem[i];
            r[i].visibilidade = true;
        }
        if (i == 4) {
            r[i].x = 250;
            r[i].y = 65;
            r[i].xDaLargura = 30;
            r[i].yDaAltura = 30;
            r[i].imagem = imagem[i];
            r[i].visibilidade = true;
        }
        if (i == 5) {
            r[i].x = 333;
            r[i].y = 125;
            r[i].xDaLargura = 30;
            r[i].yDaAltura = 30;
            r[i].imagem = imagem[i];
            r[i].visibilidade = true;
        }
        if (i == 6) {
            r[i].x = 10;
            r[i].y = 300;
            r[i].xDaLargura = 30;
            r[i].yDaAltura = 30;
            r[i].imagem = imagem[i];
            r[i].visibilidade = true;
        }
        if (i == 7) {
            r[i].x = 80;
            r[i].y = 100;
            r[i].xDaLargura = 30;
            r[i].yDaAltura = 30;
            r[i].imagem = imagem[i];
            r[i].visibilidade = true;
        }
        if (i == 8) {
            r[i].x = 60;
            r[i].y = 20;
            r[i].xDaLargura = 30;
            r[i].yDaAltura = 30;
            r[i].imagem = imagem[i];
            r[i].visibilidade = true;
        }
        if (i == 9) {
            r[i].x = 100;
            r[i].y = 300;
            r[i].xDaLargura = 30;
            r[i].yDaAltura = 30;
            r[i].imagem = imagem[i];
            r[i].visibilidade = true;
        }
    }

    al_start_timer(temporizador);

    while (true) {
        al_wait_for_event_timed(filaDeAcoes, &acoes, 0.01);

        if (acoes.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (acoes.keyboard.keycode) {
            case ALLEGRO_KEY_A:
                key[0] = true;
                break;
            case ALLEGRO_KEY_D:
                key[1] = true;
                break;
            case ALLEGRO_KEY_W:
                key[2] = true;
                break;
            case ALLEGRO_KEY_S:
                key[3] = true;
                break;
            case ALLEGRO_KEY_LEFT:
                key[4] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                key[5] = true;
                break;
            case ALLEGRO_KEY_UP:
                key[6] = true;
                break;
            case ALLEGRO_KEY_DOWN:
                key[7] = true;
                break;
            }
        }
        else if (acoes.type == ALLEGRO_EVENT_KEY_UP) {
            switch (acoes.keyboard.keycode) {
            case ALLEGRO_KEY_A:
                key[0] = false;
                break;
            case ALLEGRO_KEY_D:
                key[1] = false;
                break;
            case ALLEGRO_KEY_W:
                key[2] = false;
                break;
            case ALLEGRO_KEY_S:
                key[3] = false;
                break;
            case ALLEGRO_KEY_LEFT:
                key[4] = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                key[5] = false;
                break;
            case ALLEGRO_KEY_UP:
                key[6] = false;
                break;
            case ALLEGRO_KEY_DOWN:
                key[7] = false;
                break;
            }
        }
        else if (acoes.type == ALLEGRO_EVENT_KEY_CHAR) {
            if (acoes.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                break;
            }
        }
        else if (acoes.type == ALLEGRO_EVENT_TIMER) {
            if (key[0] || key[4])
                r[0].x -= velocidadeDoPersonagem;
            if (key[1] || key[5])
                r[0].x += velocidadeDoPersonagem;
            if (key[2] || key[6])
                r[0].y -= velocidadeDoPersonagem;
            if (key[3] || key[7])
                r[0].y += velocidadeDoPersonagem;
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(imagemDeFundo, 0, 0, 0);
        for (int i = 0; i < numeroDeRetangulos; i++) {
            desenhandoRetangulo(r[i]);
        }

        for (int i = 1; i < numeroDeRetangulos; i++) {
            if (hitBox(r[0], r[i])) {
                r[i].visibilidade = false;
            }
            else {
                r[i].visibilidade = true;
            }
        }

        al_flip_display();
    }

    al_destroy_bitmap(imagemDeFundo);
    for (int i = 0; i < numeroDeRetangulos; i++) {
        al_destroy_bitmap(imagem[i]);
    }
    al_destroy_timer(temporizador);
    al_destroy_event_queue(filaDeAcoes);
    al_destroy_display(tela);

    return 0;
}
