#include <iostream>
using namespace std;
template<class T>
class FIFO {
protected:
  T* Adata; //Apuntador a la pila
  int lMax; //Máximo de
  int aCur; // posición
  int aErr;
  int aStep; //como se va a mover dentro de la pila
public:
  FIFO(int pMax, int pStep = 0);
  ~FIFO(void );
  T top();
  T push(T pVal);
  void pop(void );
  bool isEmpty(void);
  bool isFull(void );
  int Error(void);
  T get(int position);
  T operator[](int position);
  void repr(void );
  int  show_sumatoria();
  void return_primos();


private:
  int sum_total ;
  void resize(void );
};

template<class T>
FIFO<T>::FIFO(int pMax, int pStep) {
  Adata = NULL; //Apuntador a la pila
  lMax = 0; //Máximo de
  aCur= 0;
  aErr=0;
  aStep=pStep; //Es la cantidad de celdas que se pueden agregar
  sum_total = 0;
  if(pMax > 0){
    lMax = pMax;
    Adata = new T[lMax] ; //Adata va a apuntar a Lmax osea al ultimo elemento de la pila
    if (Adata == NULL){
      aErr = -2;
      cout<<"No hay memoria disponible"<<endl;

    }

  }else {
    aErr = -1;
    cout << "Fuera del rango del tipo de dato elegido" << endl;
  }
  // constructor

}
template<class T>
FIFO<T>::~FIFO(void ){

  int lMax = 0; //Máximo de
  int aCur= 0;
  int aErr=0;
  int aStep=0;
  int sum_total = 0;

  if (Adata){
    delete [] Adata;
  }
  else{
    cout<<"Adata no apunta a nada"<<endl;
  }
}

template<class T>
int FIFO<T>::show_sumatoria() {

  if (sum_total > 0 ){
    return sum_total;
  } else{
    cout<<"No se ha sacado a nadie de la cola"<<endl;
    return 0;
  }

}

/*
template<class T>
int FIFO<T>::sumatoria() {
  int aMax = 0;
  T* lData = NULL;
  int x = 0 ;
  int y = 0;
  lData = new T[lMax];
  if (lData){
    for (int i = 0; i < lMax; ++i) {
      lData[i] = Adata[i];
      x += lData[i];
    }
  }
  cout<<"El valor de lmax es: "<<lMax<<endl;
  cout<<"El valor de x es: "<<x<<endl;
  delete[]lData;
  return x;
}
*/
template<class T>
T FIFO<T>::push(T pVal) {
  //pVal es el valor como tal el usuario mete
  aErr = 0;
  if(Adata){
    if (!isFull()){
      Adata[aCur] = pVal; // Le asignamos un espacio al valor dentro de la pila
      aCur++; //Le sumamos para que pueda almacenarse en el siguiente.
      return pVal;
    }
    else if (aStep !=0){
      resize();
      if (aErr ==0){
        Adata[aCur]= pVal;
        aCur++;
        return pVal;
      }
    } else{aErr = -3;cout<<"Fallo el rezise"<<endl;}
  }
}
template<class T>
T FIFO<T>::top() {
  if (Adata){
    if (!isEmpty()){
      return Adata[0]; //Es menos uno porque el último sería la dirección de memoria
    } else{
      aErr = -4;
    }
  }
  return (T)0; //Regresa un valor null
}
template<class T>
void FIFO<T>::pop() {
  if (Adata){
    if (!isEmpty()){
      sum_total += Adata[0];
      for (int i = 0; i < lMax-1; ++i) {
        Adata[i] = Adata[i+1];
        // Recorremos cada uno de los elementos de los cuales
        // Para que se copien, pero perdemos el primer valor de la cola porque queda vacía la última celda
      }
      lMax--; //Borramos
      aCur--; //Le restamos para que se pueda eliminar
    } else{
      aErr =-5;
      cout<<"Error al borrar"<<endl;
    }
  }
}

template<class T>
bool FIFO<T>::isFull() {
  return (aCur==lMax);
}
template<class T>
bool FIFO<T>::isEmpty() {
  return (aCur==0);
}
template<class T>
T FIFO<T>::get(int position) {
  if (Adata){
    if (!isEmpty()){
      if (position >=0 && aCur >position ){
        return Adata[position]; //REGRESA UNA COPIA
      } else{
        cout<<"Intento de get fuera de rango "<<endl;
        aErr =-7;
      }
    } else{cout<<"Intento de get en vacio"<<endl;aErr = -6;}
  }
}
template<class T>
T FIFO<T>::operator[](int position) {
  return get(position);
}
template<class T>
void FIFO<T>::resize() {
  int aMax = 0;
  T* lData = NULL;
  if (Adata){
    if (aStep > 0){
      aMax = lMax + aStep;
      lData = new T[aMax];
      if (lData){
        for (int i = 0; i < aMax; ++i) {
          lData[i] = Adata[i];
        }
        delete[]Adata;
        Adata = lData;
        lMax = aMax;
      }
    }
  }
}


int main() {

  FIFO<int>Pila = FIFO<int>(1, 1);
  Pila.push(1);
  Pila.push(3);
  cout<<Pila.top()<<endl;
  Pila.pop();
  cout<<Pila.top()<<endl;
  Pila.push(9);
  cout<<Pila.show_sumatoria()<<endl;
  Pila.pop();
  cout<<Pila.show_sumatoria()<<endl;
  cout<<Pila.top()<<endl;


  return 0;
}