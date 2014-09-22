Compiled from "P1.java"
public class ru.nsu.fit.djachenko.javaperfomance.task1.lab2.P1 {
  public ru.nsu.fit.djachenko.javaperfomance.task1.lab2.P1();
    Code:
       0: aload_0       
       1: invokespecial #1                  // Method java/lang/Object."<init>":()V
       4: return        

  public static void main(java.lang.String[]);
    Code:
       0: ldc           #2                  // String 
       2: astore_1      
       3: iconst_0      
       4: istore_2                          //i = 0
       5: iload_2                           //i
       6: sipush        10000               //i 10000
       9: if_icmpge     45                  //i < 10000
      12: new           #3                  // class java/lang/StringBuilder
      15: dup           
      16: invokespecial #4                  // Method java/lang/StringBuilder."<init>":()V
      19: aload_1       
      20: invokevirtual #5                  // Method java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
      23: ldc           #6                  // String  
      25: invokevirtual #5                  // Method java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
      28: iload_2       
      29: invokestatic  #7                  // Method java/lang/String.valueOf:(I)Ljava/lang/String;
      32: invokevirtual #5                  // Method java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
      35: invokevirtual #8                  // Method java/lang/StringBuilder.toString:()Ljava/lang/String;
      38: astore_1      
      39: iinc          2, 1
      42: goto          5
      45: getstatic     #9                  // Field java/lang/System.out:Ljava/io/PrintStream;
      48: aload_1       
      49: invokevirtual #10                 // Method java/lang/String.length:()I
      52: invokevirtual #11                 // Method java/io/PrintStream.println:(I)V
      55: return        
}
