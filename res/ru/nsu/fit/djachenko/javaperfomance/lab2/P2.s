Compiled from "P2.java"
public class ru.nsu.fit.djachenko.javaperfomance.P2ublic ru.nsu.fit.djachenko.javaperfomance.lab2.P2  Code:
       0: aload_0       
       1: invokespecial #1                  // Method java/lang/Object."<init>":()V
       4: return        

  public static void main(java.lang.String[]);
    Code:
       0: new           #2                  // class java/lang/StringBuilder
       3: dup           
       4: invokespecial #3                  // Method java/lang/StringBuilder."<init>":()V
       7: astore_1      
       8: iconst_0      
       9: istore_2      
      10: iload_2       
      11: sipush        10000
      14: if_icmpge     37
      17: aload_1       
      18: ldc           #4                  // String  
      20: invokevirtual #5                  // Method java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
      23: iload_2       
      24: invokestatic  #6                  // Method java/lang/String.valueOf:(I)Ljava/lang/String;
      27: invokevirtual #5                  // Method java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
      30: pop           
      31: iinc          2, 1
      34: goto          10
      37: getstatic     #7                  // Field java/lang/System.out:Ljava/io/PrintStream;
      40: aload_1       
      41: invokevirtual #8                  // Method java/lang/StringBuilder.length:()I
      44: invokevirtual #9                  // Method java/io/PrintStream.println:(I)V
      47: return        
}
