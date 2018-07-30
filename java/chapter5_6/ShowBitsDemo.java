class ShowBits{
    int numberBits; 
    ShowBits(int size){
    numberBits = size;
    }

    void show(long val){
        long mask = 1;

        mask <<= numberBits - 1;
        int spacer = 0;
        for (; mask != 0 ; mask >>>=1){
            if ((val & mask) != 0) System.out.print("1");
            else System.out.print("0");
            spacer++;
            if ((spacer % 8) == 0){
                System.out.print(" "); 
            }
        }
        System.out.println();
    }
}    


class ShowBitsDemo{
    public static void main(String args[]){
    int teste = 4097;
    ShowBits toBit = new ShowBits(32);
    
    toBit.show(teste);
    }
}
