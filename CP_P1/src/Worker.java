import java.util.Random;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.atomic.AtomicInteger;

public class Worker extends Thread {

    private int simulations, local_counter;

    public Worker(int simulations) {
        this.local_counter = 0;
        this.simulations = simulations;
    }

    private void simulate() {

        System.out.println("Thread started, simulating " + simulations + " points");

        float x, y;
        for (int i = 0; i < simulations; i++) {

            x = ThreadLocalRandom.current().nextFloat();
            y = ThreadLocalRandom.current().nextFloat();

            if (x * x + y * y <= 1)
                local_counter++;
        }
    }


    @Override
    public void run() {
        this.simulate();
    }


    public int getLocal_counter() {
        return local_counter;
    }
}

