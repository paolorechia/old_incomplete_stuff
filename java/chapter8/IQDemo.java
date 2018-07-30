class FixedQueue implements ICharQ{
    private char q[]; 
    private int putloc, getloc;

    public FixedQueue (int size){
        q = new char[size];
        putloc = getloc = 0;
    }
    public void put(char ch){
        if (putloc < q.length){
            q[putloc] = ch;
            putloc++;
        }
        else{
            if (putloc != getloc){
                System.out.println("Queue is full.");
            }
            else{
                System.out.println("Queue is wasted.");
            }
        }
    }
    public char get(){
        if (getloc < q.length && getloc != putloc){
            int i = getloc;
            getloc++;
            return q[i];
        }
        if (getloc == q.length){
            System.out.println("Queue is wasted.");
        }
        else System.out.println("Queue is empty.");    
        return (char) 0;
    }
}
class CircularQueue implements ICharQ{
    private char q[]; 
    private int putloc, getloc;

    public CircularQueue (int size){
        q = new char[size + 1];
        putloc = getloc = 0;
    }
    public void put(char ch){
        if (((putloc + 1) % q.length) != getloc){
            q[putloc]=ch;
            putloc = (putloc + 1) % q.length;
        }
        else{
            System.out.println("Queue is full.");
        }
    }
    public char get(){
        if (getloc != putloc){
            int aux = getloc;
            getloc = (getloc + 1) % q.length;
            return q[aux];
        }
        System.out.println("Queue is empty!");    
        return (char) 0;
    }
}

class DynamicQueue implements ICharQ{
    private char q[]; 
    private int putloc, getloc;

    public DynamicQueue (int size){
        q = new char[size];
        putloc = getloc = 0;
    }
    public void put(char ch){
        if (putloc == q.length){
            char[] t = new char[q.length * 2];
            for (int i = 0; i < q.length; i++){
                t[i] = q[i];
            }
            q = t;
        }
        q[putloc++]=ch;
    }
    public char get(){
        if (putloc == getloc){
            System.out.println("Queue is empty!");    
            return (char) 0;
        }
        return q[getloc++];
    }
}

class IQDemo {
    public static void main(String args[]){
        System.out.println("This is a demo.\n");
        System.out.println("Behold... the Fixed Queue!\n");
        int size = 10;
        char letra;
        FixedQueue fixed = new FixedQueue(size);    
        for (int i = 0; i<size + 1; i++){
            letra = (char) (i + 97);
            fixed.put(letra);
        }
        for (int i = 0; i<size + 1; i++){
            letra = fixed.get();
            System.out.print(letra);
        }
        for (int i = 0; i<size + 1; i++){
            letra = (char) (i + 97);
            fixed.put(letra);
        }
        for (int i = 0; i<size + 1; i++){
            letra = fixed.get();
            System.out.print(letra);
        }
        System.out.println();
        System.out.println("Behold... the Circular Queue!\n");
        size = 9;
        CircularQueue circular = new CircularQueue(size);    
        for (int i = 0; i<size + 1; i++){
            letra = (char) (i + 97);
            circular.put(letra);
        }
        for (int i = 0; i<size + 1; i++){
            letra = circular.get();
            System.out.print(letra);
        }
        for (int i = 0; i<size + 1; i++){
            letra = (char) (i + 65);
            circular.put(letra);
        }
        for (int i = 0; i<size + 1; i++){
            letra = circular.get();
            System.out.print(letra);
        }
        System.out.println();

        System.out.println("Behold... the Dynamic Queue!\n");
        DynamicQueue dynamic = new DynamicQueue(size);    
        for (int i = 0; i<size + 1; i++){
            letra = (char) (i + 97);
            dynamic.put(letra);
        }
        for (int i = 0; i<size + 1; i++){
            letra = dynamic.get();
            System.out.print(letra);
        }
        for (int i = 0; i<size + 1; i++){
            letra = (char) (i + 65);
            dynamic.put(letra);
        }
        for (int i = 0; i<size + 1; i++){
            letra = dynamic.get();
            System.out.print(letra);
        }
        System.out.println();
    }
}
