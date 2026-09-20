#include "sprites.h"
#include <iostream>
#include <string>
#include <random>
#include <cctype>

using namespace std;

struct Jugador {

  string nombre_del_jugador;
  string clase_del_jugador;

  int escudo = 5;
  int vida;
  int ataque;
  int oro;
};

struct Enemigo {
    string clase_de_contricante;
    int vida;
    int ataque;
};

// FUNCIONES
void limpiarPantalla() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void Elegir_batalla(struct Jugador& jugador);
void Reino_Mago(struct Jugador& jugador);




int main() {

  Jugador jugador;

  // ANTES DE EMPEZAR
  cargando_sprite_de_bienvenida();
  cout << "Hola aventurer@, como te llamas?: ";
  getline(cin, jugador.nombre_del_jugador);
  cout << "Bienvenid@ " << jugador.nombre_del_jugador
       << " porfavor eliga su rol  (presione nuevamente ENTER) " << endl;
  fflush(stdin);
  cin.get();
  std::cout << R"(
    +++++++++++++++
    + 1.Guerrero  +
    + 2.Mago      +
    + 3.Arquero   +
    + 4.Vagabundo +
    +++++++++++++++
    )" << std::endl;
  cout << "-> ";
  getline(cin, jugador.clase_del_jugador);
  for (std::size_t i = 0; i < jugador.clase_del_jugador.size(); ++i) {
    jugador.clase_del_jugador[i] = static_cast<char>(
        std::toupper(static_cast<unsigned char>(jugador.clase_del_jugador[i])));
  }

  if (jugador.clase_del_jugador == "GUERRERO") {
    jugador.vida = 18;
    jugador.ataque = 14;
    jugador.oro = 181;
  } else if (jugador.clase_del_jugador == "ARQUERO") {
    jugador.vida = 10;
    jugador.ataque = 16;
    jugador.oro = 180;
  } else if (jugador.clase_del_jugador == "MAGO") {
    jugador.vida = 8;
    jugador.ataque = 19;
    jugador.oro = 180;
  } else if (jugador.clase_del_jugador == "VAGABUNDO") {
    jugador.vida = 12;
    jugador.ataque = 12;
    jugador.oro = 66;
  }

  limpiarPantalla();
 
while (jugador.vida > 0)
{
    Elegir_batalla(jugador);
};

  return 0;

}

void Reino_Mago(struct Jugador& jugador) { // Siempre trabajar con el Jugador Original.

    // Obtener una semilla aleatoria del sistema
    string clases_mago[] = {
        "Mago oscuro",
        "Mago de fuego",
        "Mago de hielo",
        "Mago de la tormenta",
        "Mago de la oscuridad"
    };

    random_device rd;
    mt19937 gen(rd());

    // Definir rangos
    uniform_int_distribution<int> vida_aleatoria(15, 50);
    uniform_int_distribution<int> ataque_aleatorio(20, 58);
    uniform_int_distribution<int> probabilidad(1, 100);
    uniform_int_distribution<int> probabilidad_de_contrincante(1, 5);
    uniform_int_distribution<int> money(3, 100);

    // Generando enemigo
    Enemigo mago_oscuro;
    mago_oscuro.clase_de_contricante =
        clases_mago[probabilidad_de_contrincante(gen) - 1];
    mago_oscuro.vida = vida_aleatoria(gen);
    mago_oscuro.ataque = ataque_aleatorio(gen);

    // Generando variable para explorar
    int alerta = 0;
    bool salida = false;

    while (!salida) {

        cout << "\n¿Qué deseas hacer en este lugar?" << endl;
        cout << "1. Explorar el bosque oscuro (Deambular)" << endl;
        cout << "2. Descansar un momento" << endl;
        cout << "Selecciona una opción: ";

        cin >> alerta;

        int opcion_de_compra;
        int item_a_comprar;
        int suerte = probabilidad(gen);

        switch (alerta) {

            case 1:

                cout << "Explorando el bosque oscuro..." << endl;
                cout << "\nCaminas entre la niebla del Reino Mago..." << endl;

                if (suerte <= 47) {

                    cout << "(Enemigo cerca)!" << endl;

                    Enemigo mago_oscuro;
                    mago_oscuro.clase_de_contricante =
                        clases_mago[probabilidad_de_contrincante(gen) - 1];
                    mago_oscuro.vida = vida_aleatoria(gen);
                    mago_oscuro.ataque = ataque_aleatorio(gen);

                    int Enemigo_recibe_ataque = jugador.ataque;
                    int Jugador_recibe_ataque = mago_oscuro.ataque;
                    int opcion_de_batalla = 0;

                    bool combate = true;

                    limpiarPantalla();

                    cout << "Pelear contra un "
                         << mago_oscuro.clase_de_contricante
                         << " con HP de: "
                         << mago_oscuro.vida
                         << " puntos de vida"
                         << endl;

                    cout << "Tu HP es de: "
                         << jugador.vida
                         << " puntos de vida"
                         << endl;

                    // ===== COMBATE =====

                    while (combate && mago_oscuro.vida > 0 && jugador.vida > 0) {

                        cout << "\n1. Atacar" << endl;
                        cout << "2. Atacar con escudo (ataque reducido)" << endl;
                        cout << "3. Huir" << endl;

                        cout << "Selecciona una opción: ";
                        cin >> opcion_de_batalla;

                        switch (opcion_de_batalla) {

                            case 1:

                                cout << "Atacando..." << endl;

                                mago_oscuro.vida -= Enemigo_recibe_ataque;

                                if (mago_oscuro.vida > 0) {
                                    jugador.vida -= Jugador_recibe_ataque;
                                }

                                cout << "HP "
                                     << mago_oscuro.clase_de_contricante
                                     << " = "
                                     << mago_oscuro.vida
                                     << endl;

                                cout << "HP "
                                     << jugador.nombre_del_jugador
                                     << " = "
                                     << jugador.vida
                                     << endl;

                                break;

                            case 2:

                                cout << "Usando escudo..." << endl;

                                jugador.escudo -= 1;

                                if (jugador.escudo < 0) {
                                    jugador.escudo = 0;
                                    jugador.vida -= Jugador_recibe_ataque;

                                    cout << "Tu escudo se ha agotado. "
                                         << "No puedes usarlo más."
                                         << endl;
                                }
                                else {
                                    cout << "Escudo restante "
                                         << "(el uso es limitado): "
                                         << jugador.escudo
                                         << endl;
                                }

                                mago_oscuro.vida -= Enemigo_recibe_ataque / 10;

                                cout << "HP "
                                     << mago_oscuro.clase_de_contricante
                                     << " = "
                                     << mago_oscuro.vida
                                     << endl;

                                cout << "HP "
                                     << jugador.nombre_del_jugador
                                     << " = "
                                     << jugador.vida
                                     << endl;

                                break;

                            case 3:

                                cout << "Huyendo..." << endl;

                                combate = false;

                                break;

                            default:

                                cout << "Opcion invalida" << endl;
                                cout << "No supistes que hacer y el enemigo te ataco..."
                                     << endl;

                                jugador.vida -= Jugador_recibe_ataque;

                                cout << "HP "
                                     << jugador.nombre_del_jugador
                                     << " = "
                                     << jugador.vida
                                     << endl;

                                if (jugador.vida <= 0) {
                                    limpiarPantalla();
                                    salida = true;
                                }

                                break;
                        }
                    }

                    // ===== FIN DEL COMBATE =====

                    if (mago_oscuro.vida <= 0) {
                      limpiarPantalla();
                      level_up();
                        cout << "\n¡Has derrotado a un enemigo!" << endl;

                        jugador.vida += 10;

                        cout << "Tu HP ahora es de: "
                             << jugador.vida
                             << endl;

                        jugador.ataque += 5;

                        cout << "Tu ataque ahora es de: "
                             << jugador.ataque
                             << endl;

                        jugador.oro += money(gen);

                        cout << "Oro conseguido es de: "
                             << jugador.oro
                             << endl;
                             
                    }
  
                }

                if (jugador.vida <= 0) {
                   salida = true;
                    break;
                }

                break;

            case 2:
            cout<<"Quieres comprar algun item?"<<endl;
            cout<<"1. Si"<<endl;
            cout<<"2. No"<<endl;
            cout<<"-> ";
            
            cin>>opcion_de_compra;

            if (opcion_de_compra == 1) {
                limpiarPantalla();
                tienda();
                cin>>item_a_comprar;
                switch(item_a_comprar){
                    case 1:
                        if(jugador.oro >= 101){
                            jugador.escudo += 5;
                            jugador.oro -= 101;
                            cout<<"Has comprado un encantamiento para tu escudo."<<endl;
                        } else {
                            cout<<"No tienes suficiente oro para comprar esto."<<endl;
                        }
                        break;
                    case 2:
                        if(jugador.oro >= 66){
                            jugador.vida += 3;
                            jugador.oro -= 66;
                            cout<<"Has comprado una pocion de vida."<<endl;
                        } else {
                            cout<<"No tienes suficiente oro para comprar esto."<<endl;
                        }
                        break;
                    case 3:
                        if(jugador.oro >= 2000){
                            jugador.ataque += 12;
                            jugador.oro -= 2000;
                            cout<<"Has comprado una espada de diamante."<<endl;
                        } else {
                            cout<<"No tienes suficiente oro para comprar esto."<<endl;
                        }
                        break;
                    case 4:
                        if(jugador.oro >= 2000){
                            jugador.escudo += 12;
                            jugador.oro -= 2000;
                            cout<<"Has comprado un escudo de diamante."<<endl;
                        } else {
                            cout<<"No tienes suficiente oro para comprar esto."<<endl;
                        }
                        break;
                    case 5:
                        if(jugador.oro >= 200){
                            jugador.vida += 5;
                            jugador.oro -= 200;
                            cout<<"Has comprado una pocion de vida extra."<<endl;
                        } else {
                            cout<<"No tienes suficiente oro para comprar esto."<<endl;
                        }
                        break;
                    default:
                        cout<<"Opcion invalida."<<endl;
                }

            } else if (opcion_de_compra == 2) {
                cout << "Has decidido no comprar nada." << endl;
            } else {
                cout << "Opcion invalida." << endl;
            }

                break;

            default:

                cout << "Opcion invalida." << endl;
                break;
        }
    }
    limpiarPantalla();

    cout << "Nombre: "
         << jugador.nombre_del_jugador
         << endl;

    cout << "HP: "
         << jugador.vida
         << endl;

    cout << "Ataque: "
         << jugador.ataque
         << endl;

         if (jugador.vida <= 0) {
            cout << "Game Over. Has sido derrotado." << endl;
            limpiarPantalla();
          you_died();
            salida = true;
          } else {
            cout << "¡Felicidades! Has sobrevivido a un ataque." << endl;
            limpiarPantalla();
            level_up();
          }
}


void Elegir_batalla(struct Jugador& jugador) {
  cargando_sprite_del_mapa();
  cout << "Donde desea pelear?" << endl;
  cout << "-> ";

  int opcion_donde_pelear;
  cin >> opcion_donde_pelear;

  if (opcion_donde_pelear == 1) {
    cout << "Entrando." << endl;
    Reino_Mago(jugador); 
  } else {
    cout << "Opcion invalida." << endl;
  }
}