import java.io.*;
public class cortaAspas{
    public static void main (String args[]){
        if (args.length == 0){
            System.out.println("Uso: java cortaAspas arg1 [arg2] ... [argN]");
        }

       try (InputStream inputStream = new FileInputStream(args[0]);
            OutputStream outputStream = new FileOutputStream("clean_" + args[0]))
        {
            Reader in = new InputStreamReader(inputStream);
            Writer out = new OutputStreamWriter(outputStream); 
           
            int test = in.read();
           
            while(test != -1){
                if (test == '”' || test == '“'){

                    test = '"';
                }
                out.write(test);
                out.flush();
                test=in.read();
            }

        } catch(IOException exc){
            System.out.println("I/O Error:" + exc);
            }
        }
}
