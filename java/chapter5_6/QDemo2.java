class Queue{
    private char q[];
    private int putloc, getloc;

    Queue(int size){
        q = new char[size];
        putloc = getloc = 0;
    }

    Queue(Queue object){
        putloc = object.putloc;
        getloc = object.getloc;
        q = new char[object.q.length];

        for (int i = getloc; i < putloc; i++){
            q[i]=object.q[i];
        }
    }
    Queue(String word){
        q = new char[word.length()];
        putloc = getloc = 0;
        for (int i = 0; i < word.length(); i++){
           put(word.charAt(i));
        }
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
    public String flush(){
        char extract;
        char[] array = new char[100];
        int i = 0;
        while ( (extract = get()) != 0 && i < 100){
            System.out.print((char) extract);
            array[i]=extract;
            i++;
        }
        System.out.println();
        String my_string = new String(array);
        return my_string;
    }
}

class QDemo2{
    public static void main(String args[]){
        int size = 5;
        Queue my_queue = new Queue(size);
        int i;
        for (i = 0 ; i < size ; i++){
            my_queue.put((char) ('a' + i));
        } 
        Queue copy_queue = new Queue(my_queue);
        for (i = 0 ; i < size ; i++){
            System.out.print(my_queue.get());
            System.out.println();
        } 
        for (i = 0 ; i < size ; i++){
            System.out.print(copy_queue.get());
            System.out.println();
        } 
        Queue third_queue = new Queue("Este eh um teste\n");
        String another_string = new String(third_queue.flush());
        System.out.println(another_string);
    }
}
