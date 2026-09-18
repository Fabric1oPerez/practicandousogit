#include <iostream>

// PARTE 1: Modelado del elemento
struct Elemento {
    int codigo;
    std::string nombre;
    float longitud;
    float cargas[3];          
    float capacidadMaxima;
    float factorUtilizacion;
    std::string estadoSeguridad;
};

//PARTE 2: registro de elementos
void registrarElemento(Elemento &elemento){
    std::cout << "Codigo: ";
    std::cin >> elemento.codigo;
    std::cin.ignore();                       
    std::cout << "Nombre: ";
    std::getline(std::cin, elemento.nombre);
    std::cout << "Longitud: ";
    std::cin >> elemento.longitud;
    std::cout << "Carga 1: ";
    std::cin >> elemento.cargas[0];
    std::cout << "Carga 2: ";
    std::cin >> elemento.cargas[1];
    std::cout << "Carga 3: ";
    std::cin >> elemento.cargas[2];
    std::cout << "Capacidad maxima: ";
    std::cin >> elemento.capacidadMaxima;
}

//PARTE 3: calculo del factor de utilizacion
float calcularFactor(Elemento *elemento){
    float promedio = (elemento->cargas[0] + elemento->cargas[1] + elemento->cargas[2]) / 3;
    float factor = promedio / elemento->capacidadMaxima;
    elemento->factorUtilizacion = factor;   
    return factor;
}

// PARTE 4: determinacion del estado de seguridad
void determinarSeguridad(Elemento &elemento){
    if(elemento.factorUtilizacion <= 0.50)
        elemento.estadoSeguridad = "SEGURO";
    else if(elemento.factorUtilizacion <= 0.80)
        elemento.estadoSeguridad = "PRECAUCION";
    else if(elemento.factorUtilizacion <= 1.00)
        elemento.estadoSeguridad = "RIESGO";
    else
        elemento.estadoSeguridad = "SOBRECARGA";
}

// PARTE 5: identificacion del elemento mas comprometido
Elemento* obtenerElementoCritico(Elemento elementos[], int cantidad){
    Elemento *critico = &elementos[0];

    for(int i = 1; i < cantidad; i++){
        if(elementos[i].factorUtilizacion > critico->factorUtilizacion){
            critico = &elementos[i];   
        }
    }
    return critico;
}

// PARTE 6: simulacion de incremento de carga
void aumentarCargas(Elemento &elemento, float porcentaje){
    for(int i = 0; i < 3; i++){
        elemento.cargas[i] = elemento.cargas[i] * (1 + porcentaje / 100);
    }

    calcularFactor(&elemento);    
    determinarSeguridad(elemento);
}

// PARTE 7: informe
void generarInforme(Elemento elementos[], int cantidad){
    int seguros = 0, precaucion = 0, riesgo = 0, sobrecarga = 0;
    float sumaFactores = 0;

    for(int i = 0; i < cantidad; i++){
        float promedio = (elementos[i].cargas[0] + elementos[i].cargas[1] + elementos[i].cargas[2]) / 3;

        std::cout << elementos[i].codigo << " - " << elementos[i].nombre
             << " | carga promedio: " << promedio
             << " | factor: " << elementos[i].factorUtilizacion
             << " | estado: " << elementos[i].estadoSeguridad << std::endl;

        if(elementos[i].estadoSeguridad == "SEGURO") seguros++;
        else if(elementos[i].estadoSeguridad == "PRECAUCION") precaucion++;
        else if(elementos[i].estadoSeguridad == "RIESGO") riesgo++;
        else sobrecarga++;

        sumaFactores += elementos[i].factorUtilizacion;
    }

    std::cout << "\nSeguros: " << seguros << "  Precaucion: " << precaucion
         << "  Riesgo: " << riesgo << "  Sobrecarga: " << sobrecarga << std::endl;
    std::cout << "Factor de utilizacion promedio: " << (sumaFactores / cantidad) << std::endl;
}


int main(){
    Elemento elementos[10];
    int cantidad;

    do {
        std::cout << "Cuantos elementos deseas registrar (1-10): ";
        std::cin >> cantidad;
    } while(cantidad < 1 || cantidad > 10);

    for(int i = 0; i < cantidad; i++){
        registrarElemento(elementos[i]);
    }


    for(int i = 0; i < cantidad; i++){
        calcularFactor(&elementos[i]);      
        determinarSeguridad(elementos[i]);
    }

    
    Elemento *critico = obtenerElementoCritico(elementos, cantidad);
    std::cout << "\n--- Elemento mas comprometido ---" << std::endl;
    std::cout << critico->codigo << " - " << critico->nombre
         << " | factor: " << critico->factorUtilizacion
         << " | estado: " << critico->estadoSeguridad << std::endl;

    float porcentaje;
    std::cout << "\nPorcentaje de incremento a simular sobre el elemento critico: ";
    std::cin >> porcentaje;
    aumentarCargas(*critico, porcentaje);  
    std::cout << "Nuevo factor: " << critico->factorUtilizacion
         << " | Nuevo estado: " << critico->estadoSeguridad << std::endl;

    
    std::cout << "\n--- Informe final ---" << std::endl;
    generarInforme(elementos, cantidad);

    return 0;
}



