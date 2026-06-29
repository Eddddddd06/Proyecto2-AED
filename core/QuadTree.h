#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include "Particula.h"

struct Limite {
    float centro_x;
    float centro_y;
    float mitad_ancho;
    float mitad_alto;

    bool contiene(const Particula& particula) const;
    bool intersecta(const Limite& otro) const;
};

class QuadTree {
private:
    Limite limite;
    int capacidad;
    std::vector<Particula> particulas;
    bool dividido;

    QuadTree* node_noroeste;
    QuadTree* node_noreste;
    QuadTree* node_suroeste;
    QuadTree* node_sureste;

    void subdividir();

public:
    QuadTree(Limite limite_inicial, int capacidad_maxima);
    ~QuadTree();

    bool insertar(const Particula& particula);
    std::vector<Particula> buscar(const Limite& rango) const;
};

#endif
