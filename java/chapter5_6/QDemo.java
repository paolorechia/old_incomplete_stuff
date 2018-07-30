class Queue{
    private char q[];
    private int putloc, getloc;

    Queue(int size){
        q = new char[size];
    }

    public void put(char input){
        if (putloc < q.length){
            q[putloc]=(char)input;
            putloc++;
        }
        else{
            System.out.println("Queue is full!\n");
        }
    }
    public char get(){
        if (getloc != putloc){
            char result = q[getloc];
            getloc++;   
            return result;
        }
        System.out.println("Queue is empty!\n");
        return (char) 0;
    }
}

class QDemo{
    public static void main(String args[]){
        int size = 5;
        Queue my_queue = new Queue(size);
        int i;
        for (i = 0 ; i < size ; i++){
            my_queue.put((char) ('a' + i));
        } 
        for (i = 0 ; i < size ; i++){
            System.out.print(my_queue.get());
            System.out.println();
        } 
    }
}
