class FixedQueue implements ICharQ{
    private char q[]; 
    private int putloc, getloc;

    public FixedQueue (int size){
        q = new char[size];
        putloc = getloc = 0;
    }
    public void put(char ch)
    throws QueueFullException{
        if (putloc < q.length){
            q[putloc] = ch;
            putloc++;
        }
        else{
            if (putloc != getloc){
                throw new QueueFullException(q.length);
            }
            else{
                System.out.println("Queue is wasted.");
            }
        }
    }
    
    public char get()
    throws QueueEmptyException{
        if (getloc < q.length && getloc != putloc){
            int i = getloc;
            getloc++;
            return q[i];
        }
        throw new QueueEmptyException();
    }
}

class QExcDemo {
    public static void main(String args[]){
        System.out.println("This is a demo.\n");
        int size = 10;
        char letra;
        FixedQueue fixed = new FixedQueue(size);    
        try{
            for (int i = 0; i<size + 1; i++){
                letra = (char) (i + 97);
                fixed.put(letra);
            }
        }
        catch (QueueFullException exc){
            System.out.println(exc);
        }
        try{
            for (int i = 0; i<size + 1; i++){
                letra = fixed.get();
                System.out.print(letra);
            }
        }
        catch (QueueEmptyException exc){
            System.out.println(exc);
        }
        System.out.println();
    }
}
