public class Main {

    public static void main(String[] args) {


        int sim_num = Integer.parseInt(args[0]);
        int threadNr = 1;

        System.out.println("Number of threads: " + args[1]);
        System.out.println("Number of points: " + sim_num);
        System.out.println();

        if (args.length == 2) {
            threadNr = Integer.parseInt(args[1]);
            assert threadNr >= 1;
        }

        int sim_per_thread = sim_num / threadNr;

        Worker[] workers = new Worker[threadNr];
        int remainder = sim_num % threadNr;

        for (int i = 0; i < threadNr; i++, remainder--) {

            workers[i] = (remainder > 0) ? new Worker(sim_per_thread + 1) : new Worker(sim_per_thread);
            workers[i].start();

        }

        for (Worker t : workers) {
            try {
                t.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        int sum = 0;
        for (Worker worker : workers) sum += worker.getLocal_counter();

        System.out.println("hit_counter= " + sum);

        float p = (float) sum / sim_num;
        float pi = p * 4;


        System.out.println("pi: " + pi);


    }


}
