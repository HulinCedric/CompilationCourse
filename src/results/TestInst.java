/**
 * TestInst.java
 * 
 * @author C. Hulin
 */

import java.awt.Graphics;
import java.applet.Applet;

public class TestInst extends Applet {
    
    public void proc1(Graphics g) {}
    
    public int fonc1(Graphics g) {
        int A = 0;
        return A;
    }
    
    public void paint(Graphics g) {
        int x;
        x = 10;
        int y = x;
        int z = 100;
        Mulot leMulot = new Mulot(z, 200, Mulot.RED, g);
        leMulot.leve(g);
    }
}
