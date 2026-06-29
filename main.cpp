#include <iostream>
#include "core/Simulador.cpp"

// === PUNTO DE ENTRADA ===

int main() {
    std::cout << "Iniciando prueba de logica del QuadTree y Simulador..." << std::endl;
    
    Simulador simulador(800.0f, 600.0f);
    
    Particula p1 = {100.0f, 100.0f, 10.0f, 5.0f, 2.0f, 1};
    Particula p2 = {200.0f, 200.0f, -5.0f, 10.0f, 2.0f, 2};
    Particula p3 = {150.0f, 150.0f, 0.0f, 0.0f, 2.0f, 3};
    
    simulador.agregar_particula(p1);
    simulador.agregar_particula(p2);
    simulador.agregar_particula(p3);
    
    std::cout << "Avanzando frame..." << std::endl;
    simulador.avanzar_frame(1.0f);
    
    for (const auto& particula : simulador.obtener_particulas()) {
        std::cout << "Particula " << particula.id << " -> X: " << particula.x << ", Y: " << particula.y << std::endl;
    }
    
    std::cout << "Prueba finalizada exitosamente." << std::endl;
    
    return 0;
}
