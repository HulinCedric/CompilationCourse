/**
 * TestDessin.java
 * 
 * @author C. Hulin
 */

import java.awt.Graphics;
import java.applet.Applet;

public class TestDessin extends Applet {
    
    public void Dessin(Mulot m, int cote, Graphics g) {
        m.avance(cote, g);
        m.tourne(90, g);
        m.avance(cote, g);
        m.tourne(90, g);
        m.avance(cote, g);
        m.tourne(90, g);
        m.avance(cote, g);
        m.tourne(90, g);
    }
    
    public void paint(Graphics g) {
        int z = 100;
        Mulot leMulot = new Mulot(z, 200, Mulot.RED, g);
        leMulot.baisse(g);
        Dessin(leMulot, 200, g);
    }
}
