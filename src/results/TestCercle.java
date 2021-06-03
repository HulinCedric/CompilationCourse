/**
 * TestCercle.java
 * 
 * @author C. Hulin
 */

import java.awt.Graphics;
import java.applet.Applet;

public class TestCercle extends Applet {
    public void paint(Graphics g) {
        Mulot m = new Mulot(g);
        m.baisse(g);
        int b = 12;
        int c = 360 / b;
        for (int i = 1; i <= b; i++) {
            m.avance(15, g);
            m.tourne(c, g);
        }
        m.leve(g);
        m.avance(100, g);
    }
}
