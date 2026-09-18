#include <iostream>

using namespace std;

struct Elemento{
    int codigo;
    string nombre;
    float longitud;
    float cargas[3];
    float capMAx;
    float facUt;
    string estSeg;
};
const int elementosMAx = 10;

void registrarElemento(Elemento &elemento){

    cout<<"***Bienvenido al registro de elementos***"<<endl;
    cout<<"Ingrese el codigo: "<<endl;
    cin>>ws>> elemento.codigo;
    cout<<"Ingrese el nombre: "<<endl;
    cin>> elemento.nombre;
    cout<<"Ingrese su longitud: "<<endl;
    cin>> elemento.longitud;
    
    for(int i = 0; i < 3; i++)
    {
        cout<<"Ingrese la carga "<<i + 1<<" (en Newtons): "<<endl;
        cin>> elemento.cargas[i];
    }

    cout<<"Ingrese la capacidad maxima: "<<endl;
    cin>> elemento.capMAx;
}

void maxElem(Elemento elementos[], int &cantidad)
{

    do
    {
        cout<<"Ingrese la cantidad de elementos (Max. 10): ";
        cin>>cantidad;

       if(cantidad > elementosMAx)
       {
        cout<<"Cantidad de elementos invalido, intente de nuevo"<<endl;
       } 
       
    } while (cantidad > elementosMAx || cantidad < 1);

    for(int i = 0; i < cantidad; i++)
    {
        registrarElemento(elementos[i]);
    }
    
}

float calcularFactor(Elemento *elemento){
    float suma = 0;
    float *p = elemento ->cargas; //Recibir un puntero a un Elemento

    for(int i= 0; i<3; i++){
        suma += *p;
        p++;
    }

    float cargaProm = suma/3;

    float CalcFacUt = cargaProm / elemento->capMAx;

    elemento->facUt = CalcFacUt;

    return CalcFacUt;
}

void determinarSeguridad(Elemento &elemento){
    if(elemento.facUt >= 0.00 && elemento.facUt <= 0.50 ){
        elemento.estSeg = "SEGURO";
    }
    else if(elemento.facUt > 0.50 && elemento.facUt <= 0.80 ){
        elemento.estSeg = "PRECAUCION";
    }
    else if(elemento.facUt > 0.80 && elemento.facUt <= 1.00 ){
        elemento.estSeg = "RIESGO";
    }
    else if(elemento.facUt > 1.00){
        elemento.estSeg = "SOBRECARGA";
    }
}

Elemento* obtenerElementoCritico(Elemento elementos[],int cantidad){
    Elemento *elementoCritico = &elementos[0];

    for(int i=1; i < cantidad; i++){
        if(elementos[i].facUt > elementoCritico->facUt){
            elementoCritico = &elementos[i];
        }
    }
    return elementoCritico;
}

void mostrarElemento(Elemento *elemento) {
    cout << "***elemento con mayor factor de utilizacion***" << endl;
    cout << "Codigo: " << elemento->codigo << endl;
    cout << "Nombre: " << elemento->nombre << endl;
    cout << "Longitud: " << elemento->longitud << endl;
    cout << "Carga 1: " << elemento->cargas[0] << endl;
    cout << "Carga 2: " << elemento->cargas[1] << endl;
    cout << "Carga 3: " << elemento->cargas[2] << endl;
    cout << "Capacidad maxima: " << elemento->capMAx << endl;
    cout << "Factor de utilizacion: " << elemento->facUt << endl;
    cout << "Estado: " << elemento->estSeg << endl;
}

void aumentarCargas(Elemento &elemento, float porcentaje){
    char respuesta;
    
    cout << "Desea aumentar las cargas del elemento? [s/n]"<<endl;
    cin >> respuesta;

    if(respuesta == 's' || respuesta == 'S'){
        for(int i = 0; i < 3; i++){
            cout << "Ingrese el porcentaje de aumento para la carga " << i + 1 << ", ingrese en [1-100]: ";
            cin >> porcentaje;
            elemento.cargas[i] = elemento.cargas[i] * (1 + porcentaje/100);
        }
    }
}

void generarInforme(Elemento elementos[], int cantidad){
    int contSeguro = 0;
    int contPrecaucion = 0;
    int contRiesgo = 0;
    int contSobrecarga = 0;
    float sumaFactores = 0;

    cout<<"***Informe general de elementos***"<<endl;
    for(int i = 0; i<cantidad; i++){
        float cargaProm = (elementos[i].cargas[0] + elementos[i].cargas[1] + elementos[i].cargas[2])/3.0;
        cout<<"Elemento: "<< i + 1 <<endl;
        cout<<"Codigo:"<<elementos[i].codigo<<endl;
        cout<<"Nombre:"<<elementos[i].nombre<<endl;
        cout<<"Carga promedio: "<<cargaProm<<endl;
        cout<<"Factor de utilizacion:"<<elementos[i].facUt<<endl;
        cout<<"Estado:"<<elementos[i].estSeg<<endl;

        if(elementos[i].estSeg == "SEGURO"){
            contSeguro++;
        }
        else if(elementos[i].estSeg == "PRECAUCION"){
            contPrecaucion++;
        }
        else if(elementos[i].estSeg == "RIESGO"){
            contRiesgo++;
        }
        else if(elementos[i].estSeg == "SOBRECARGA"){
            contSobrecarga++;
        }

         sumaFactores += elementos[i].facUt;
    }

    float factPromGeneral = sumaFactores/cantidad;

    cout<<"***Resumen por estado***"<<endl;
    cout<<"SEGURO: "<<contSeguro<<endl;
    cout<<"PRECAUCION: "<<contPrecaucion<<endl;
    cout<<"RIESGO: "<<contRiesgo<<endl;
    cout<<"SOBRECARGA: "<<contSobrecarga<<endl;
    cout<<"Factor de utilizacion de toda la estructura: "<<factPromGeneral<<endl;
    
}


int main(){
    Elemento elementos[elementosMAx];
    int cantidad;
    float porcentaje;
    maxElem(elementos,cantidad);

    for(int i = 0; i < cantidad; i++){
        calcularFactor(&elementos[i]);
        determinarSeguridad(elementos[i]);
    }
    
    Elemento* elemComprometido = obtenerElementoCritico(elementos, cantidad);
    mostrarElemento(elemComprometido);

    aumentarCargas(*elemComprometido, porcentaje);

    calcularFactor(elemComprometido);
    determinarSeguridad(*elemComprometido);
    
    mostrarElemento(elemComprometido);

    generarInforme(elementos, cantidad);


    return 0;
}