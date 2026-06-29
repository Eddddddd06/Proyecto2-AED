#include "QuadTree.h"

// === LIMITES Y CAJAS ===

bool Limite::contiene(const Particula& particula) const {
    return (particula.x >= centro_x - mitad_ancho &&
            particula.x <= centro_x + mitad_ancho &&
            particula.y >= centro_y - mitad_alto &&
            particula.y <= centro_y + mitad_alto);
}

bool Limite::intersecta(const Limite& otro) const {
    return !(otro.centro_x - otro.mitad_ancho > centro_x + mitad_ancho ||
             otro.centro_x + otro.mitad_ancho < centro_x - mitad_ancho ||
             otro.centro_y - otro.mitad_alto > centro_y + mitad_alto ||
             otro.centro_y + otro.mitad_alto < centro_y - mitad_alto);
}

// === CONSTRUCTOR Y DESTRUCTOR ===

QuadTree::QuadTree(Limite limite_inicial, int capacidad_maxima) {
    limite = limite_inicial;
    capacidad = capacidad_maxima;
    dividido = false;
    node_noroeste = nullptr;
    node_noreste = nullptr;
    node_suroeste = nullptr;
    node_sureste = nullptr;
}

QuadTree::~QuadTree() {
    if (dividido) {
        delete node_noroeste;
        delete node_noreste;
        delete node_suroeste;
        delete node_sureste;
    }
}

// === FASE 1: INSERCION ===

void QuadTree::subdividir() {
    float x = limite.centro_x;
    float y = limite.centro_y;
    float w = limite.mitad_ancho / 2.0f;
    float h = limite.mitad_alto / 2.0f;

    node_noroeste = new QuadTree({x - w, y - h, w, h}, capacidad);
    node_noreste = new QuadTree({x + w, y - h, w, h}, capacidad);
    node_suroeste = new QuadTree({x - w, y + h, w, h}, capacidad);
    node_sureste = new QuadTree({x + w, y + h, w, h}, capacidad);

    dividido = true;
}

bool QuadTree::insertar(const Particula& particula) {
    if (!limite.contiene(particula)) {
        return false;
    }

    if (particulas.size() < capacidad) {
        particulas.push_back(particula);
        return true;
    }

    if (!dividido) {
        subdividir();
    }

    if (node_noroeste->insertar(particula)) return true;
    if (node_noreste->insertar(particula)) return true;
    if (node_suroeste->insertar(particula)) return true;
    if (node_sureste->insertar(particula)) return true;

    return false;
}

// === FASE 2: BUSQUEDA ===

std::vector<Particula> QuadTree::buscar(const Limite& rango) const {
    std::vector<Particula> resultados;

    if (!limite.intersecta(rango)) {
        return resultados;
    }

    for (const auto& particula : particulas) {
        if (rango.contiene(particula)) {
            resultados.push_back(particula);
        }
    }

    if (dividido) {
        std::vector<Particula> resultados_noroeste = node_noroeste->buscar(rango);
        resultados.insert(resultados.end(), resultados_noroeste.begin(), resultados_noroeste.end());

        std::vector<Particula> resultados_noreste = node_noreste->buscar(rango);
        resultados.insert(resultados.end(), resultados_noreste.begin(), resultados_noreste.end());

        std::vector<Particula> resultados_suroeste = node_suroeste->buscar(rango);
        resultados.insert(resultados.end(), resultados_suroeste.begin(), resultados_suroeste.end());

        std::vector<Particula> resultados_sureste = node_sureste->buscar(rango);
        resultados.insert(resultados.end(), resultados_sureste.begin(), resultados_sureste.end());
    }

    return resultados;
}
