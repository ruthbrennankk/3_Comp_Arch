public class Ackermann {

    //Global Variables
    static int nWindows;
    static int wused;

    static int call_count;

    static int overflows;
    static int underflows;

    static int depth;
    static int maxDepth;


    static void enter() {
        call_count++;
        depth++;
        if (depth > maxDepth)
            maxDepth = depth;
        if (wused == nWindows) {
            overflows++;
        } else {
            wused++;
        }
    }

    static void exit() {
        depth--;
        if (wused == 2) {	// always need 2 valid windows
            underflows++;
        } else {
            wused--;
        }
    }

    static int ackermann_with_checks(int x, int y) {
        enter();
        int temp;
        if (x == 0) {
            temp = y + 1;
        } else if (y == 0) {
            temp =  ackermann_with_checks(x - 1, 1);
        } else {
            temp = ackermann_with_checks(x - 1, ackermann_with_checks(x, y - 1));
        }
        exit();
        return temp;
    }

    static void run(int nwindows) {
        //Initalisations
        nWindows = nwindows;
        wused = 2;  //Always need two windows
        call_count = 0;
        overflows = 0;
        underflows = 0;
        depth = 0;
        maxDepth = 0;

        //Function Call
        int result = ackermann_with_checks(3, 6);

        //Output
        System.out.println("ackermann(3, 6) = " + result);
        System.out.println("The register set = " + nWindows);
        System.out.println("Number of procedure calls = " + call_count);
        System.out.println("The Number of Register Window overflows = " + overflows);
        System.out.println("The Number of Register Window underflows = " + underflows);
        System.out.println("The maximum register window depth = " + maxDepth);

        if (overflows != underflows)
            System.out.print("Error: Underflows should equal overflows");
    }

    static int ackermann_without_checks(int x, int y) {
        if (x == 0) {
            return y + 1;
        } else if (y == 0) {
            return ackermann_without_checks(x - 1, 1);
        } else {
            return ackermann_without_checks(x - 1, ackermann_without_checks(x, y - 1));
        }
    }

    public static void main (String args[]) {

        //run with different register sets and use ackermann with checks so that it will keep track of calls, overflow, underflow and depth
       run(6);
       run(8);
       run(16);

       //This is working to calculate the execution time
        //I run the ackermann function (without checks) multiple times and find the average
        //I find the average of 1,000,000 executions because that was enough for me to feel satisfied with the degree of accuracy
        //I use the system time as I found it to be a better alternative to System.currentTimeMillis()
        //However I did read that it is not entirely accurate to the nanosecond
        //Of course, the accuracy of measurements varies widely depending on operating system, hardware and Java version.
        //I took plenty of averages to attempt to even out any inaccuracy that may be incurred as a result of these dependencies
        int number = 1000000;
        long duration_sum = 0;
        for (int i =0; i<number; i++ ) {
            long startTime = System.nanoTime();
            ackermann_without_checks(3,6);
            long endTime = System.nanoTime();
            duration_sum += (endTime - startTime);
        }
        long averageTime = duration_sum/number;

       System.out.println("Execution time of ackermann function (in ns) = " + averageTime);
    }

}
