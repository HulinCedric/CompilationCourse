/**
 * TestCarre.java
 * 
 * @author C. Hulin
 */

import java.awt.Graphics;
import java.applet.Applet;

public class TestCarre extends Applet {
    
    public void Carre(int x, int y, int d, Graphics g) {
        Mulot m = new Mulot(x, y, Mulot.RED, g);
        m.baisse(g);
        int nb = 50;
        for (int i = 0; i <= 7; i++) {
            m.avance(nb, g);
            m.tourne(-90, g);
            m.avance(nb, g);
            m.tourne(-90, g);
            m.avance(nb, g);
            m.tourne(-90, g);
            m.avance(nb, g);
            m.tourne(-90, g);
            m.leve(g);
            m.avance(d, g);
            m.tourne(-90, g);
            m.avance(d, g);
            m.tourne(90, g);
            m.baisse(g);
            nb = nb - 12;
        }
        m.leve(g);
    }
    
    public void paint(Graphics g) {
        int delta = 6;
        int y = 10;
        int jDeb;
        int j;
        int x;
        for (int i = 1; i <= 5; i++) {
            if ((i == 1) || (i == 3) || (i == 5)) {
                jDeb = 1;
                x = 10;
            }
            else {
                jDeb = 2;
                x = 110;
            }
            j = jDeb;
            while (j <= 5) {
                Carre(x, y, delta, g);
                x = x + 200;
                j = j + 2;
            }
            y = y + 100;
        }
    }
}
