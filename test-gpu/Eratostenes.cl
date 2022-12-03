__kernel void prototyp1(__global int* data, int size, int rootSize)
{
    size_t Gindex = get_global_id(0);
    int element = Gindex%size;
    element +=1;
    int dzielnik = Gindex / size;
    dzielnik +=1;
    if(dzielnik == 1) 
    {
        data[1] = get_local_size(0);
        return;
    }
    if(element == dzielnik) return;
    else if(element%dzielnik == 0)
    {
        data[element] = -1;
    }
    //data[element] = element;
}

__kernel void prototyp11(__global char* data, int rootSize)
{
    long int index = (get_global_id(1) * get_global_size(0)) + get_global_id(0); //pobranie indeksu
    int element = index/rootSize; //wyliczenie, jaką liczbę będziemy dzielić
    element +=2; //dodanie 2 (bo liczymy od 2, a nie od 0)
    int dzielnik = index % rootSize; //wyliczenie dzielnika
    dzielnik +=2; //dodanie 2 (bo dzielimy od 2, a nie od 0)
    if(element == dzielnik) return; //jeśli dzielnik jest taki sam jak element
    else if(element%dzielnik == 0)
    {
        data[element] = -1; //jeśli reszta z dzielenia daje 0, to liczba nie jest pierwsza, i ją wykreślamy
    }
    //data[element] = element;
}

 __kernel void p12(__global char* data, __global int* data2, int divN) 
{
    long int index = (get_global_id(1) * get_global_size(0)) + get_global_id(0);
    int element = index/divN;
    element +=2;
    int dzielnik = index % divN;
    int primeDzielnik = data2[dzielnik];
    if(element == primeDzielnik) return;
    else if(element%primeDzielnik == 0)
    {
        data[element] = 0;
    }
    //data[element] = divN;
}

 __kernel void wersja1(__global char* data, __global int* data2, int divN, int rootn) 
{
    int element = (get_global_id(1) * get_global_size(0)) + get_global_id(0); //wyliczenie indeksu
    element +=rootn; //dodanie pierwiastka z N (bo od tego zakresu liczymy)
    int Dzielnik=0; 
    for(int i=0; i<divN; i++) //dzielenie elementu, przez każdy z dzielnikow
    {
        Dzielnik = data2[i];
        if(element == Dzielnik) continue;
        if(element%Dzielnik == 0) //jeśli element jest podzielny, to znaczy ze nie jest liczbą piewszą, usuwamy więc go z sita, i kończymy sprawdzanie elementu
        {
            data[element] = data[element] >> 1;
            //data[element] = 0;
            return;
        }
    }
    //data[element] = divN;
}

__kernel void wersja2(__global char* data, __global int* data2, long int size) 
{
    long int index = (get_global_id(1) * get_global_size(0)) + get_global_id(0);
    int dzielnik = data2[index];
    for(int i=2; i<size; i++)
    {
        if(i == dzielnik) continue;
        if(i%dzielnik == 0)
        {
            data[i] = 0;
        }
    }
    //data[element] = divN;
}


__kernel void prototyp2(__global int* data, int div)
{
    size_t index = get_global_id(0);
    index +=2;
    if(index == div) return;
    else if(index%div == 0)
    {
        data[index] = -1;
    }
    //data[index] = index;
}

__kernel void test1(__global int* data,__global int* data2)
{
    long long int index = (get_global_id(1) * get_global_size(0)) + get_global_id(0);
    data[index] = data2[index];

}

__kernel void test2(__global int* data3, __global int* data4)
{
    size_t index = get_global_id(0);
    data3[index] = index;
}
