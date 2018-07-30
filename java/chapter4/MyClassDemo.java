class MyClass{
    int x;
    
    MyClass (int i) {
        x = i;
    }
}

class MyClassDemo{
    public static void main(String args[]){
        MyClass t1 = new MyClass(10);
        MyClass t2 = new MyClass(83);
        System.out.println(t1.x + " " + t2.x);
    }
}
