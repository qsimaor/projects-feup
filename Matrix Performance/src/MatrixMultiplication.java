import java.util.Scanner;

public class MatrixMultiplication {
    public static void OnMult(int m_ar, int m_br) {

        long Time1, Time2;
        String st;
        double temp;
        int i, j, k;
        double[] pha, phb, phc;

        pha = new double[m_ar * m_ar];
        phb = new double[m_ar * m_ar];
        phc = new double[m_ar * m_ar];

        for (i = 0; i < m_ar; i++)
            for (j = 0; j < m_ar; j++)
                pha[i * m_ar + j] = 1.0;

        for (i = 0; i < m_br; i++)
            for (j = 0; j < m_br; j++)
                phb[i * m_br + j] = i + 1;

        Time1 = System.currentTimeMillis();

        for (i = 0; i < m_ar; i++) {
            for (j = 0; j < m_br; j++) {
                temp = 0;
                for (k = 0; k < m_ar; k++) {
                    temp += pha[i * m_ar + k] * phb[k * m_br + j];
                }
                phc[i * m_ar + j] = temp;
            }
        }

        Time2 = System.currentTimeMillis();

        st = "Time: " + (double) (Time2 - Time1) / 1000 + " seconds\n";
        System.out.println(st);

        System.out.println("Result matrix: ");
        for (i = 0; i < 1; i++) {
            for (j = 0; j < Math.min(10, m_br); j++)
                System.out.print(phc[j] + " ");
        }
        System.out.println();
    }

    public static void OnMultLine(int m_ar, int m_br) {

        long Time1, Time2;
        String st;
        int i, j, k;
        double[] pha, phb, phc;

        // Alocação de memória
        pha = new double[m_ar * m_ar];
        phb = new double[m_ar * m_ar];
        phc = new double[m_ar * m_ar];

        // Matriz A
        for(i = 0; i < m_ar; i++)
            for(j = 0; j < m_ar; j++)
                pha[i * m_ar + j] = 1.0;

        // Matriz B
        for(i = 0; i < m_br; i++)
            for(j = 0; j < m_br; j++)
                phb[i * m_br + j] = i + 1;

        // Matriz C
        for(i = 0; i < m_ar; i++)
            for(j = 0; j < m_br; j++)
                phc[i * m_ar + j] = 0.0;

        // Início do tempo
        Time1 = System.currentTimeMillis();

        // Multiplicação das matrizes
        for (i = 0; i < m_ar; i++) {
            for (j = 0; j < m_ar; j++) {
                for (k = 0; k < m_br; k++) {
                    phc[i * m_ar + j] += pha[i * m_ar + k] * phb[k * m_br + j];
                }
            }
        }

        // Fim do tempo
        Time2 = System.currentTimeMillis();

        // Cálculo do tempo
        st = "Time: " + (double) (Time2 - Time1) / 1000 + " seconds\n";
        System.out.println(st);

        // display 10 elements of the result matrix tto verify correctness
        System.out.println("Result matrix: ");
        for (i = 0; i < 1; i++) {
            for (j = 0; j < Math.min(10, m_br); j++)
                System.out.print(phc[j] + " ");
        }
        System.out.println();
    }

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            int lin, col;
            int op;
            op = 1;
            do {
                System.out.println("\n1. Multiplication");
                System.out.println("2. Line Multiplication");
                System.out.print("Selection?: ");
                op = scanner.nextInt();
                if (op == 0)
                    break;
                System.out.print("Dimensions: lins=cols ? ");
                lin = scanner.nextInt();
                col = lin;

                switch (op) {
                    case 1:
                        OnMult(lin, col);
                        break;
                    case 2:
                        OnMultLine(lin, col);
                        break;
                }
            } while (op != 0);
        }
    }
}

