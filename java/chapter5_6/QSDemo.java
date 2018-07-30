import java.util.Random;

class Quicksort {
    static void qsort(char items[]){
        qs(items, 0, items.length-1);
    }
    private static void qs(char items[], int left, int right){

        int i, j;
        char x = items[(left + right) / 2];
        char y;
    
        i = left;
        j = right;

        do{
        while (items[i] < x && i < right) i++;
        while (items[j] > x && j > left) j--;

        if (i <= j){
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
        } while (i <= j); 

        if (left  < j) qs(items, left, j);
        if (right > i) qs(items, i, right);
    }
}
class QSDemo{
    public static void main (String args[]){
        Random rnd = new Random();
        int number;
        int size = 10;
        int i;
        char[] my_array = new char[size];
        for (i = 0; i < size; i++){
            number = rnd.nextInt(23);   
            my_array[i]=(char)(number + 97);
            System.out.print(my_array[i]);
        }
        System.out.println();
        Quicksort.qsort(my_array); 
        for (i = 0; i < size; i++){
            System.out.print(my_array[i]);
        }
        System.out.println();
    }
}
