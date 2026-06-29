#include <vector>
#include "Particula.h"
#include "QuadTree.h"

// === MOTOR DE SIMULACION ===

class Simulador {
private:
    std::vector<Particula> particulas;
    float ancho_mundo;
    float alto_mundo;

public:
    Simulador(float ancho, float alto) {
        ancho_mundo = ancho;
        alto_mundo = alto;
    }

    void agregar_particula(const Particula& particula) {
        particulas.push_back(particula);
    }

    void avanzar_frame(float delta_tiempo) {
        for (auto& particula : particulas) {
            particula.x += particula.velocidad_x * delta_tiempo;
            particula.y += particula.velocidad_y * delta_tiempo;

            if (particula.x < 0 || particula.x > ancho_mundo) {
                particula.velocidad_x *= -1;
            }
            if (particula.y < 0 || particula.y > alto_mundo) {
                particula.velocidad_y *= -1;
            }
        }

        Limite limite_mundo = {ancho_mundo / 2.0f, alto_mundo / 2.0f, ancho_mundo / 2.0f, alto_mundo / 2.0f};
        QuadTree quadtree(limite_mundo, 4);

        for (const auto& particula : particulas) {
            quadtree.insertar(particula);
        }
        
        // Aqui se puede usar quadtree.buscar() para procesar colisiones en este frame
    }

    std::vector<Particula> obtener_particulas() const {
        return particulas;
    }
};
