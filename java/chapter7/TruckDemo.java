class Vehicle {
    int passengers;
    int fuelcap;
    int mpg;

    Vehicle(int p, int f, int m){
    passengers = p;
    fuelcap = f;
    mpg = m;
    }

    int range(){
        return mpg * fuelcap;
    }

    double fuelneeded(int miles){
        return (double) miles/mpg;
    }

    int     getPassengers()     {return passengers;}
    void    setPassengers(int p){passengers = p;}
    int     getFuelcap ()       {return fuelcap;}
    void    setFuelcap(int f)   {fuelcap    = f;}
    int     getMpg()            {return mpg;}
    void    setMpg(int m)       {mpg = m;}

}
class Truck extends Vehicle {
    private int cargocap;

    Truck(int p, int f, int m, int c){
    super(p, f, m);
    cargocap = c;
    }

    int  getCargo()      { return cargocap;}
    void putCargo(int c) {cargocap = c;} 
}

class TruckDemo{
    public static void main(String args[]){
        Truck caminhao = new Truck(2, 60, 5, 300);
        int p = caminhao.getPassengers();
        int m = caminhao.getFuelcap();
        int c = caminhao.getMpg();
        double f = caminhao.fuelneeded(40);
        System.out.println(p);
        System.out.println(m);
        System.out.println(c);
        System.out.println(f);
    }
}
