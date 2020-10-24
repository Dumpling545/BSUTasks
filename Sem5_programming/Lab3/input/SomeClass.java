public class SomeClass {
    public static int iSquare(int a){
        return a*a;
    }
    public static long lSquare(long a){
        return a*a;
    }
    public static double dSquare(double a){
        return a*a;
    }
    public static double iSquare(double a){
        return a*a;
    }
    public static float fSquare(float a){
        return a*a;
    }
    public static String toUpperCase(String s){
        return s.toUpperCase();
    }
    public static double addAndPossiblyRound(double a, double b, boolean shouldRound){
        double c = a + b;
        if(shouldRound) c = Math.round(c);
        return c;
    }
}
